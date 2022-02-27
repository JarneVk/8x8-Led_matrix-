/*
 * uart_ontvanger.c
 *
 * Created: 21/02/2022 16:03:28
 *  Author: Gebruiker
 */ 

/*
usart onvanger zorgt voor de low level aansturing van de usart poorten die aan de IRED worden gekoppeld 

het zal enkel ontvangen en kan hierop zelf antwoorden met NACK(packet) of ACK(packet)
*/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "HeaderMatrix.h"

#define NAME3(a,b,c)         NAME3_HIDDEN(a,b,c)
#define NAME3_HIDDEN(a,b,c)  a ## b ## c

#define initIrcomUsart(ARG) \
NAME3(USART,ARG,_BAUDL) = 0xB6;\
NAME3(USART,ARG,_BAUDH) = 0x02;\
NAME3(USART,ARG,_CTRLC) = 0x3E;  //00111110 -> 9bit verzending


void uartsetup(){
	initIrcomUsart(0);
	PORTA_DIRSET = 0x01;
	USART0_CTRLB = 0xC0;
	
	initIrcomUsart(1);
	PORTC_DIRSET = 0x01;
	USART0_CTRLB = 0xC0;
	
	ontvanger_verbinding = 0;
	ontvanger_buffer_uart0 = 0;
	ontvanger_count_timeout = 0;
}


void timer_setup(){
	//TCB0_CTRLA mag op default 0 blijven 
	TCB0_CTRLB = 0x01;		//timeout mode
	TCB0_INTCTRL = 0x01;	//enable inetrups
	TCB0_CNT = 0x00;		//zet timer op 0
	TCB0_CCMPL = 0xFF;
	TCB0_CCMPH = 0xFF;
	TCB0_EVCTRL = 0x01; 	// op 0x01 om de timer te starten 
}


/* SendData : de ontvanger zal een ACK(frame) een NACK(frame) kunnen sturen naar de zender
		ACK :   1 0000 0001
		NACK :	1 0000 0010	

 */

/* send data : we kiezen voor 8 bit verzending -> CHSIZE in Control C moet op 8 bit staan
    als er data in TXDATAL word geschreven zal deze in de TX buffer komen en serieel worden doorgestuurd
    je kan ENKEL in het register schrijven als DREIF (in usartn.status) bit op 1 staat
*/

int sendData_usart0(int hexgetal){   // returnt een 0 als het kan verzonden zorden anders een 1
    if(USART0_STATUS&(1<<5)){		 // get de DREIF bit
		ontvanger_buffer_uart0 = hexgetal;
        USART0_TXDATAL = hexgetal;
        return 0;
    }    
    else {
        // register is nog niet geshift -> even wachten
        return 1;
    }
}

/* get data : in RXDATAH, bit 7 zegt of er data in de buffer zit -> eerste hiernaar kijken 
    als RXDATAH of L worden gelezen zal de buffer doorschuiven (afhankelijk van de configuratie in Control C)
    => eerst het niet schiftende register uitlezen en dan het schiftende 
    #optioneel FERR geef aan of de frame juist is toegekomen#
    #PERR parity check, een foute controle op de data #

    aanpak? 
    - eerste RXDATAH inlezen en kijken of er nieuwe data aanwezig is 
    - checken of de data goed is toegekomen met PERR/FERR
    - als alles correct is -> RXDATAL inlezen en register laten schiften
*/

void readuart0_interupt(){      // geeft 8 bits terug 
	int bits[2];
	if(USART0_RXDATAH&(1<<7)){	// kijken naar 7de bit
		bits[0] = USART0_RXDATAH;
		bits[1] = USART0_RXDATAL; 
		
		if(bits[0]&(1<<2) || bits[0]&(1<<1)){	// kijken of er geen frame of parity errors zijn
			//NACK sturen 
			while(sendData_usart0(2)){
				_delay_ms(1);
			}
		}else if(bits[0]==1 && bits[1]==2){	//NACK
			while(sendData_usart0(ontvanger_buffer_uart0)){
				_delay_ms(1);
			}
		} else{
			ontvanger_count_timeout = 0;
			//ACK sturen
			while(sendData_usart0(1)){
				_delay_ms(1);
			}
			//return bits[1];
			/*

			HIER MOET EEN HOGERE FUNCTIE KOMEN DIE DE DATA VERWERKT


			*/
		}	
	}
}


void conectie_ACK(){
	int bits[2];
	if(USART0_RXDATAH&(1<<7)){
		bits[0] = USART0_RXDATAH;
		bits[1] = USART0_RXDATAL; 
		if(bits[0]&(1<<2) || bits[0]&(1<<1)){
			//doe niks
		}
		else if(bits[0]==1 && bits[1]==1){
			ontvanger_verbinding = 1;
		}
	}
}


ISR(USART0_RXC_vect){
	if(ontvanger_verbinding == 1){
		TCB0_EVCTRL = 0x00; 	// timer stoppen en resetten 
		TCB0_CNT = 0x00;
		readuart0_interupt();
		TCB0_EVCTRL = 0x01;
	}
	else{

	}
	
}


//timeout functie 
ISR(TCB0_INT_vect){
	TCB0_EVCTRL = 0x00; 	// timer stoppen en resetten 
	TCB0_CNT = 0x00;
	if(ontvanger_verbinding == 1){
		ontvanger_count_timeout += 1;
		if(ontvanger_count_timeout == 4){		//verbinding verbroken
			ontvanger_verbinding = 0;
			ontvanger_count_timeout = 0;
		}
		while(sendData_usart0(ontvanger_buffer_uart0)){
			_delay_ms(1);
		}
	}
	else{
		while(sendData_usart0(0b10101010)){
			_delay_ms(1);
		}
	}
	TCB0_EVCTRL = 0x01;
}






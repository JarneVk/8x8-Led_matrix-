/*
 * uart_ontvanger.c
 *
 * Created: 21/02/2022 16:03:28
 *  Author: Gebruiker
 */ 

/*
usart onvanger zorgt voor de low level aansturing van de usart poorten die aan de IRED worden gekoppeld 
het zal enkel ontvangen en kan hierop zelf antwoorden met NACK(packet) of ACK(packet)

werking :	- 	Er moet een externe functie 'int writeUartData(uint8_t data)' worden aangemaakt.
				Deze functie geeft een 1 terug als ze nog data verwacht en een 0 als ze geen data meer verwacht (voor die verzending).

			- 	Dit programma zal een interupt generen als het een packetje ontvangt. 
				De errors worden automatisch afgehandeld
*/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../HeaderMatrix.h"

#define NAME3(a,b,c)         NAME3_HIDDEN(a,b,c)
#define NAME3_HIDDEN(a,b,c)  a ## b ## c

#define initIrcomUsart(ARG) \
NAME3(USART,ARG,_BAUDL) = 0xB6;\
NAME3(USART,ARG,_BAUDH) = 0x02;\
NAME3(USART,ARG,_CTRLA) = 0b11000000;\ 
NAME3(USART,ARG,_CTRLC) = 0x3E;  //00111110 -> 9bit verzending


void uartsetup_ontvanger_uart0(){
	initIrcomUsart(0);
	PORTA_DIRSET = 0x01;
	USART0_CTRLB = 0b11010000; //was 0xC0
	USART0_EVCTRL = 0x01; //disable IrDA
	
	ontvanger_buffer_uart0 = 0;

	//LED voor te testen 
	PORTC_DIR |= PIN5_bm;
	
}


/* Send Data : de ontvanger zal een ACK(frame) een NACK(frame) kunnen sturen naar de zender
		ACK :   1 0000 0001
		NACK :	1 0000 0010	
	we kiezen voor 9 bit verzending -> CHSIZE in Control C moet op 9 bit staan
    als er data in TXDATAL word geschreven zal deze in de TX buffer komen en serieel worden doorgestuurd
    je kan ENKEL in het register schrijven als DREIF (in usartn.status) bit op 1 staat
*/

int sendData_usart0(uint8_t hexgetal){   // returnt een 0 als het kan verzonden zorden anders een 1
    if(USART0_STATUS&(1<<5)){		 // get de DREIF bit
		ontvanger_buffer_uart0 = hexgetal;
        USART0_TXDATAL = hexgetal;
        return 0;
    }    
    else {
        // register is nog niet geshift
        return 1;
    }
}


/* get data : in RXDATAH, bit 7 zegt of er data in de buffer zit -> eerste hiernaar kijken 
    als RXDATAH of L worden gelezen zal de buffer doorschuiven (afhankelijk van de configuratie in Control C)
    => eerst het niet schiftende register uitlezen en dan het schiftende 
    FERR geef aan of de frame juist is toegekomen
	PERR parity check, een foute controle op de data 
*/

void readuart0_interupt(){      // geeft 8 bits terug 
	PORTC_OUT |= PIN5_bm;
	uint8_t bits[2];
	if(USART0_RXDATAH&(1<<7)){	// kijken naar 7de bit
		bits[0] = USART0_RXDATAH;
		bits[1] = USART0_RXDATAL; 
		
		if(bits[0]&(1<<2) || bits[0]&(1<<1)){	// kijken of er geen frame of parity errors zijn
			//NACK sturen 
			while(sendSpecial(2)){
				_delay_ms(1);
			}
		}else if(bits[0]==1 && bits[1]==2){	//NACK
			PORTC_OUT |= PIN5_bm;
			while(sendData_usart0(ontvanger_buffer_uart0)){
				_delay_ms(1);
			}
		} else{
			
			
			if(writeOntvangenData(bits[1]) == 0){ //HIER MOET EEN HOGERE FUNCTIE KOMEN DIE DE DATA VERWERKT
				//ACK sturen
				PORTC_OUT &= ~PIN5_bm;
				while(sendSpecial(1)){
				_delay_ms(1);
				}
			}
			else{
				while(sendSpecial(3)){
				_delay_ms(1);
				}
				ledsAansturen();
			}

			
		}	
	}
	PORTC_OUT &= ~PIN5_bm;
}


ISR(USART0_RXC_vect){
	readuart0_interupt();	
}





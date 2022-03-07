/*
 * uartZender.c
 *
 * Created: 21/02/2022 16:03:28
 *  Author: Gebruiker
 */ 
 

/*
usartZender zorgt voor de low level aansturen van de usart poorten die aan de IRED trancievers worden gekoppeld
de Zender zal werken volgens een sliding window met buffer 1, en werkt in 1 richting 
het zal dus enkel een ACK(packet) of NACK(packet) kunnen ontvangen 

werking: 	- 	Er moet een externe functie 'uint8_t getNextOutputData()' worden die de 8 bits die verzonden moeten worden terug geeft.

			- 	Om de zending te starten word 'SendNewColumn()' opgeroepen.
				Als de ontvanger nog data verwacht zal deze antwoorden met ACK of NACK

			-	Als de ontvanger 4x niet antwoord op een verzonden bericht zal dit geinterpreteerd worden als verbinding verborken.
				Er zal geen nieuwe data gevraagd worden tot de 'SendNewColumn()' opnieuw wordt opgeroepen
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "../HeaderMatrix.h"

#include "../Test/uart_test.c"

#define NAME3(a,b,c)         NAME3_HIDDEN(a,b,c)
#define NAME3_HIDDEN(a,b,c)  a ## b ## c

#define initIrcomUsart(ARG) \
NAME3(USART,ARG,_BAUDL) = 0xB6;\
NAME3(USART,ARG,_BAUDH) = 0x02;\
NAME3(USART,ARG,_CTRLC) = 0x3E;  //00111110 -> 9bit verzending


void uartsetup_zender_uart1(){
	initIrcomUsart(1);
	PORTA_DIRSET = 0x01;
	USART1_CTRLB = 0xC0;

	zender_buffer_uart1 = 0;
	zender_verbinding = 0;
		
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
		verbinding request : 1 1010 1010 => 1 0xAA
	we kiezen voor 8 bit verzending -> CHSIZE in Control C moet op 8 bit staan
    als er data in TXDATAL word geschreven zal deze in de TX buffer komen en serieel worden doorgestuurd
    je kan ENKEL in het register schrijven als DREIF (in usartn.status) bit op 1 staat
*/

int sendData_zender_usart1(uint8_t hexgetal){   // returnt een 0 als het kan verzonden zorden anders een 1

	zender_buffer_uart1 = hexgetal;
    if(USART1_STATUS&(1<<5)){  // get de DREIF bit
        USART1_TXDATAL = hexgetal;
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

void SendNewColumn(){  
	zender_verbinding = 1;
	zender_count_timeout = 0;
	columnIndex = 0;
	part =0;
	sendData_zender_usart1(getNextOutputData());
}

void interup_ReadData(){
	uint8_t bits[2];
	if(USART1_RXDATAH&(1<<7)){	// kijken naar 7de bit
		bits[0] = USART1_RXDATAH;
		bits[1] = USART1_RXDATAL; 
		
		if(bits[0]&(1<<2) || bits[0]&(1<<1)){	// frame of parity errors
			//NACK sturen 		
			sendSpecial(2);
		}else if(bits[0]==1 && bits[1]&(1<<2)){	// NACK 
			while(sendData_zender_usart1(zender_buffer_uart1)){
				_delay_ms(1);
			}
		} else if(bits[0]==1 && bits[1]==3){	//END
			TCB0_EVCTRL = 0x00; 	// timer stoppen en resetten 
			TCB0_CNT = 0x00;

		}else if(bits[0]==1 && bits[1]==1){		//ACK nieuw packetje sturen
			zender_count_timeout = 0;
			while(sendData_zender_usart1(getNextOutputData())){							//
				_delay_ms(1);
			}	
		}
	}
}



ISR(USART1_RXC_vect){			//interupt register 
		TCB0_EVCTRL = 0x00; 	// timer stoppen en resetten 
		TCB0_CNT = 0x00;
		interup_ReadData();
		TCB0_EVCTRL = 0x01;
}


//timeout functie 
ISR(TCB0_INT_vect){
	TCB0_EVCTRL = 0x00; 	// timer stoppen en resetten 
	TCB0_CNT = 0x00;
	zender_count_timeout += 1;
	if(zender_count_timeout == 4){		//verbinding verbroken
		zender_verbinding = 0;
		zender_count_timeout = 0;
	}
	while(sendData_zender_usart1(ontvanger_buffer_uart0)){
		_delay_ms(1);
	}
	TCB0_EVCTRL = 0x01;
}




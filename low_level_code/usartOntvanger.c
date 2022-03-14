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

void uartsetup_ontvanger_uart0(){
	USART0_BAUD = 0x056D;
	USART0_CTRLC = 0b00100110;
	PORTA_DIRSET = 0x01;
	USART0_CTRLB = 0b11000000; 
	USART0_CTRLA = 0b10000000;
	//USART0_EVCTRL = 0x01; //disable IrDA

	ontvanger_buffer_uart0 = 0;

	//LED voor te testen 
	PORTC_DIR |= PIN7_bm;
	
}


/* Send Data : de ontvanger zal een ACK(frame) een NACK(frame) kunnen sturen naar de zender
		ACK :   1 0000 0001
		NACK :	1 0000 0010	
	we kiezen voor 9 bit verzending -> CHSIZE in Control C moet op 9 bit staan
    als er data in TXDATAL word geschreven zal deze in de TX buffer komen en serieel worden doorgestuurd
    je kan ENKEL in het register schrijven als DREIF (in usartn.status) bit op 1 staat
*/

void sendData_usart0(uint8_t hexgetal){   // returnt een 0 als het kan verzonden zorden anders een 1
    ontvanger_buffer_uart0 = hexgetal;
	while((USART0_STATUS & USART_DREIF_bm)){
		USART0_TXDATAL = hexgetal;
	}
		
        
}

// 1 voor ACK, 2 voor NACK, 3 voor EndOfMessage
void sendSpecial_ontvanger(int dat){
	ontvanger_buffer_uart0 = dat;
	while((USART0_STATUS & USART_DREIF_bm)){
		USART0_TXDATAH = 1;
		USART0_TXDATAL = dat;
	}
}


/* get data : in RXDATAH, bit 7 zegt of er data in de buffer zit -> eerste hiernaar kijken 
    als RXDATAH of L worden gelezen zal de buffer doorschuiven (afhankelijk van de configuratie in Control C)
    => eerst het niet schiftende register uitlezen en dan het schiftende 
    FERR geef aan of de frame juist is toegekomen
	PERR parity check, een foute controle op de data 
*/

void readuart0_interupt(){      // geeft 8 bits terug 

	uint8_t bits[2];
	if(USART0_RXDATAH&(1<<7)){	// kijken naar 7de bit
		bits[0] = USART0_RXDATAH;
		bits[1] = USART0_RXDATAL; 
		
		if(bits[0]&(1<<2) || bits[0]&(1<<1)){	// kijken of er geen frame of parity errors zijn
			//NACK sturen 
			sendSpecial_ontvanger(2);
		}else if(bits[0]==1 && bits[1]==2){	//NACK
			sendData_usart0(ontvanger_buffer_uart0);
		} else{
			
			
			if(writeOntvangenData(bits[1]) == 0){ //HIER MOET EEN HOGERE FUNCTIE KOMEN DIE DE DATA VERWERKT
				//ACK sturen
				sendSpecial_ontvanger(1);
			}
			else{
				PORTC_OUT |= PIN5_bm;
				sendSpecial_ontvanger(3); //END
				ledsAansturen();
				_delay_ms(1000);
				PORTC_OUT &= ~PIN5_bm;
			}

			
		}	
	}
	
}

ISR(USART0_RXC_vect){
	PORTC_OUT |= PIN7_bm;
	readuart0_interupt();	
	_delay_ms(1000);
	PORTC_OUT &= ~PIN7_bm;
}





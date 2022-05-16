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

#include <avr/pgmspace.h>	// voor print 
#include <stdio.h>

#include "../HeaderMatrix.h"


void uartsetup_ontvanger_uart0(){
	//// printf_P(PSTR("init ontvanger \n\r"));
	USART0_BAUD = 0x02B6; //19200
	USART0_CTRLC = 0b10100111;  //8 bit mode
	PORTA_DIRSET = 0x01;
	USART0_CTRLB = 0b11000000;
	USART0_CTRLA = 0b11000000;


	ontvanger_buffer_uart0 = 0;

	//LED voor te testen 
	PORTC_DIR |= PIN7_bm;
	
}

/* Speciale Data responses
		ACK :    0000 0001
		NACK :	 0000 0010	
*/



void sendData_ontvanger_usart0(uint8_t hexgetal){
	//// printf_P(PSTR("send %d \n\r"),hexgetal);
	USART0_CTRLB = 0b01000000;
	ontvanger_buffer_uart0 = hexgetal;
    while(!(USART0_STATUS & USART_DREIF_bm));
    USART0_TXDATAL = hexgetal;
}

ISR(USART0_TXC_vect){
	USART0_CTRLB = 0b11000000;
	//// printf_P(PSTR("tc \n\r"));
	USART0_STATUS |= USART_TXCIF_bm;
}


void RX_inperupt_ontvanger(){
	uint8_t bits[2];
	bits[1] = USART0_RXDATAH;
	bits[0] = USART0_RXDATAL;

	//printf_P(PSTR("ont:%d \n\r"),bits[0]);

	if(bits[1] & USART_FERR_bm || bits[1] & USART_PERR_bm){
		//NACK
		//// printf_P(PSTR("NACK \n\r"));
		sendData_ontvanger_usart0(2);
	} else{
		if(bits[1] & USART_DATA8_bm && bits[0] == 2){
			//NACK van zender -> retransmit
			sendData_ontvanger_usart0(ontvanger_buffer_uart0);
		}
		else if(bits[1] & USART_DATA8_bm  && bits[0] == 60){
			//// printf_P(PSTR("startframe \n\r"));
			//clear slave variable voor nieuw frame
			ontvang_i = 0;
			sendNewColumn();
			sendData_ontvanger_usart0(1);
		}
		else if(writeOntvangenData(bits[0]) == 0){
			sendData_ontvanger_usart0(1); //ACK
		} else {
			// END
			ontvangerEnd = 1;
			endOntvanger();
			ontvang_i=0;
			sendData_ontvanger_usart0(3);
			//printf_P(PSTR("end_o \n\r"));
			if(zenderEnd){
				driveLeds();
			}
			zenderEnd = 0;
		}
	}

}


ISR(USART0_RXC_vect){
	PORTC_OUT |= PIN7_bm;
	//// printf_P(PSTR("ontvanger interupt : "));
	RX_inperupt_ontvanger();
	PORTC_OUT &= ~PIN7_bm;
	//// printf_P(PSTR("frame: %d \n\r"),USART0_RXDATAL);
}





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
	printf_P(PSTR("init ontvanger \n\r"));
	USART0_BAUD = 0x056D;
	USART0_CTRLC = 0b00100011;  //8 bit mode
	PORTA_DIRSET = 0x01;
	USART0_CTRLB = 0b11000000;
	USART0_CTRLA = 0b10000000;
	USART0_EVCTRL = 0x01; //disable IrDA

	ontvanger_buffer_uart0 = 0;
	ontvangerNAck_count = 0;

	//LED voor te testen 
	PORTC_DIR |= PIN7_bm;
	
}

/* Speciale Data responses 
		ACK :   1 0000 0001
		NACK :	1 0000 0010	
*/
void sendData_ontvanger_usart0(uint8_t hexgetal){
    while(!(USART0_STATUS & USART_DREIF_bm));
    USART0_TXDATAL = hexgetal;
	printf_P(PSTR("send %d \n\r"),hexgetal);
}


void RX_inperupt_ontvanger(){
	uint8_t bits[2];
	bits[1] = USART0_RXDATAH;
	bits[0] = USART0_RXDATAL;

	if(bits[1] & USART_FERR_bm || bits[1] & USART_PERR_bm){
		//NACK
		printf_P(PSTR("NACK \n\r"));
		sendData_ontvanger_usart0(2);
		ontvangerNAck_count += 1;
	} else{
		ontvangerNAck_count = 0;
		printf_P(PSTR("%d \n\r"),bits[0]);
		if(writeOntvangenData(bits[0]) == 0){
			sendData_ontvanger_usart0(1);
		} else {
			// END
			sendData_ontvanger_usart0(3);
			ontvang_i=0;
			ledsAansturen();
		}
	}

}

ISR(USART0_RXC_vect){
	PORTC_OUT |= PIN7_bm;
	if(stop_antwoorden){
		//doe niks meer 
	}
	else if(ontvangerNAck_count > 4){
		ledsAansturen();
		ontvangerNAck_count = 0;
		stop_antwoorden = 1;
	} else {
		printf_P(PSTR("ontvanger interupt : "));
		RX_inperupt_ontvanger();
		PORTC_OUT &= ~PIN7_bm;
	}
}





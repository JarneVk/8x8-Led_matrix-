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

#include <avr/pgmspace.h>	//voor print
#include <stdio.h>

#include "../HeaderMatrix.h"




void uartsetup_zender_uart1(){
	printf_P(PSTR("init zender \n\r"));
	USART1_BAUD = 0x056D;
	USART1_CTRLC = 0b00100011;  //8 bit mode
	PORTC_DIRSET = 0x01;
	USART1_CTRLB = 0b11000000;
	USART1_CTRLA = 0b10000000;
	USART1_EVCTRL = 0x01; //disable IrDA

	zender_buffer_uart1 = 0;

	zender_timer_setup();

	//LED voor te testen 
	PORTC_DIR |= PIN4_bm;
	PORTC_DIR |= PIN5_bm;
		
}

void zender_timer_setup(){
	TCB1_CCMPL = 0xFF;
	TCB1_CCMPH = 0xFF;
	TCB1_CTRLA = 0b00000011;
	TCB1_CTRLB = 0x00;		//timeout mode
	TCB1_INTCTRL = 0x01;	//enable inetrups
}



void sendData_zender_usart1(uint8_t hexgetal){ 
	zender_buffer_uart1 = hexgetal;
    while(!(USART1_STATUS & USART_DREIF_bm));
	printf_P(PSTR("send %d \n\r"),hexgetal);
    USART1_TXDATAL = hexgetal;
}

void SendNewColumn(){  
	PORTC_OUT &= ~PIN5_bm;

	ontvang_i=0;

	zender_count_timeout = 0;
	columnIndex = 0;
	part =0;
	sendData_zender_usart1(getNextOutputData());
	TCB1_CTRLB = 0x00;
}

/* Speciale Data responses 
		ACK :   1 0000 0001
		NACK :	1 0000 0010	
*/

void RX_ontvanger_interupt(){	
	uint8_t data = USART1_RXDATAL;
	printf_P(PSTR(" %d \n\r"),data);
	if(data == 1){	//ACK
		sendData_zender_usart1(getNextOutputData());
	} else if(data == 2){
		sendData_zender_usart1(zender_buffer_uart1);
	} else if(data == 3){
		//stop met zenden END
		PORTC_OUT |= PIN5_bm;
		ledsAansturen();
	}

}

ISR(USART1_RXC_vect){
	printf_P(PSTR("zender interupt : "));
	RX_ontvanger_interupt();
}

ISR(TCB1_INT_vect){
	printf_P(PSTR("timeout \n\r"));
	TCB1_INTFLAGS = 0x01;
	zender_count_timeout += 1;
	if(zender_count_timeout >= 4){		//verbinding verbroken
		zender_count_timeout = 0;
		TCB1_CTRLB = 0x01;	
	}
	else{
		sendData_zender_usart1(ontvanger_buffer_uart0);
	}
}
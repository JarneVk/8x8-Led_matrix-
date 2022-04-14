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

//niet meest cleane manier om de timer te stoppen
#define START_TIMER TCB1_CTRLA = 0b00000101;
#define STOP_TIMER TCB1_CTRLA  = 0b00000100;

void zender_timer_setup(){
	printf_P(PSTR("init timeout timer \n\r"));
	
	TCB1_CCMPL = 0x00;
	TCB1_CCMPH = 0x04;
	TCB1_CTRLA = 0b00000101;
	TCB1_CTRLB = 0b00000000;		//periodic
	TCB1_INTCTRL = 0x01;	//enable inetrups
}


void uartsetup_zender_uart1(){
	printf_P(PSTR("init zender \n\r"));
	USART1_BAUD = 0x056D;
	USART1_CTRLC = 0b00100111;  //8 bit mode
	PORTC_DIRSET = 0x01;
	USART1_CTRLB = 0b11000000;
	USART1_CTRLA = 0b10000000;
	USART1_EVCTRL = 0x01; //disable IrDA

	zender_buffer_uart1 = 0;
	NAck_count = 0;

	zender_timer_setup();
		
}

void sendData_zender_usart1(uint8_t hexgetal){ 
	zender_buffer_uart1 = hexgetal;
    while(!(USART1_STATUS & USART_DREIF_bm));
	printf_P(PSTR("send %d \n\r"),hexgetal);
    USART1_TXDATAL = hexgetal;
}

void sendNewColumn(){ 
	printf_P(PSTR("senNewColumn"));
	ontvang_i=0;

	NAck_count = 0;
	zender_count_timeout = 0;
	columnIndex = 0;
	part =0;

	//zend start frame
	USART1_TXDATAH = 0x01;
	sendData_zender_usart1(60); //00111100 als onder byte voor start frame
	START_TIMER;
}

/* Speciale Data responses 
		ACK :    0000 0001
		NACK :	 0000 0010	
*/

void RX_ontvanger_interupt(){
	//reset de timout counter
	STOP_TIMER;
	TCB1_CNTL = 0x00;
	TCB1_CNTH = 0x00;	
	zender_count_timeout = 0;
	uint8_t data = USART1_RXDATAL;
	printf_P(PSTR(" %d \n\r"),data);
	if(data == 1){	//ACK
		NAck_count = 0;
		sendData_zender_usart1(getNextOutputData());
		START_TIMER;
	} else if(data == 2){ //NACK
		NAck_count += 1;
		sendData_zender_usart1(zender_buffer_uart1);
		START_TIMER;
	} else if(data == 3){
		//stop met zenden END
		TCB1_CTRLB = 0x01;
		//ledsAansturen();
		driveLeds();
	}

}

ISR(USART1_RXC_vect){
	printf_P(PSTR("zender interupt : "));
	if(NAck_count > 4){
		//stop met antwoorden
	} else{
		RX_ontvanger_interupt();
	}
	

}


ISR(TCB1_INT_vect){

	STOP_TIMER;
	TCB1_CNTL = 0x00;
	TCB1_CNTH = 0x00;
	PORTC_OUT ^= PIN5_bm;
	TCB1_INTFLAGS = 0x01;
	printf_P(PSTR("timeout \n\r"));
	zender_count_timeout += 1;
	if(zender_count_timeout >= 4){		//verbinding verbroken
		zender_count_timeout = 0;
		driveLeds();
		//ledsAansturen();	
		printf_P(PSTR("stop timer \n\r"));
	}
	else{
		sendData_zender_usart1(ontvanger_buffer_uart0);
		START_TIMER;
	}
}
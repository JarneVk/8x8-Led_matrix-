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
#define START_TIMER TCB1_CNTL = 0; TCB1_CNTH=0; timer_var=1;	 
#define STOP_TIMER timer_var=0;

uint8_t timer_var;

void zender_timer_setup(){
	
	TCB1_CCMPL = 0x00;
	TCB1_CCMPH = 0x01;
	TCB1_CTRLA = 0b00000101;
	TCB1_CTRLB = 0b00000000;		//periodic
	TCB1_INTCTRL = 0x01;	//enable inetrups
	zender_count_timeout = 0;
}


void uartsetup_zender_uart1(){
	USART1_BAUD = 0x02B6; //19200
	USART1_CTRLC = 0b10100111;  //9 bit mode
	PORTC_DIRSET = 0x01;
	USART1_CTRLB = 0b11000000;
	USART1_CTRLA = 0b11000000;

	zender_buffer_uart1 = 0;
	NAck_count = 0;
	timer_var = 0;

	zender_timer_setup();
}

/**
 * @brief zend data over usart1 
 * 
 * @param hexgetal  een 8 bit getal dat verzonden moet worden 
 */
void sendData_zender_usart1(uint8_t hexgetal){ 
	USART1_CTRLB = 0b01000000;
	zender_buffer_uart1 = hexgetal;
    while(!(USART1_STATUS & USART_DREIF_bm));
    USART1_TXDATAL = hexgetal;
}

ISR(USART1_TXC_vect){
	USART1_CTRLB = 0b11000000;
	USART1_STATUS |= USART_TXCIF_bm;
}

void sendNewColumn(){ 
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

/**
 * @brief interupt functie die wordt opgerepen 
 * als de zender een packetje ontvangt 
 */
void RX_ontvanger_interupt(){
	//reset de timout counter
	STOP_TIMER;
		
	zender_count_timeout = 0;
	uint8_t data = USART1_RXDATAL;
	uint8_t dataH = USART1_RXDATAH;
	if(dataH & (USART_FERR_bm | USART_PERR_bm)){
		//NACK
		USART1_TXDATAH = 0x01;
		sendData_zender_usart1(2);
	} else if(data == 1){	//ACK
			NAck_count = 0;
			USART1_TXDATAH = 0x00;
			sendData_zender_usart1(getNextOutputData());
			START_TIMER;
		} else if(data == 2){ //NACK
			NAck_count += 1;
			USART1_TXDATAH = 0x00;
			sendData_zender_usart1(zender_buffer_uart1);
			START_TIMER;
		} else if(data == 3){
			//stop met zenden END
			driveLeds();
			
		}

}

ISR(USART1_RXC_vect){	
	RX_ontvanger_interupt();

}


ISR(TCB1_INT_vect){
	if(timer_var){
		STOP_TIMER;	
		zender_count_timeout += 1;
		if(zender_count_timeout >= 4){		//verbinding verbroken
			zender_count_timeout = 0;
			zenderEnd = 1;
			if(ontvangerEnd || master){
				driveLeds();
			}
			ontvangerEnd = 0;
		}
		else{
			sendData_zender_usart1(zender_buffer_uart1);
			START_TIMER;
		}
	}
	TCB1_INTFLAGS = 0x01;
	
}


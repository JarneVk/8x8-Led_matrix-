

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

	//zender_timer_setup();

	//LED voor te testen 
	PORTC_DIR |= PIN4_bm;
	PORTC_DIR |= PIN5_bm;
		
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
	//TCB1_CTRLB = 0x00;
}

void RX_ontvanger_interupt(){
	
	//error chack nog bij?
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
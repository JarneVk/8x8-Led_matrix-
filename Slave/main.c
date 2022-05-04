#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <avr/pgmspace.h>


// void uartsetup_ontvanger_uart0(){
// 	printf_P(PSTR("init ontvanger \n\r"));
// 	USART0_BAUD = 0x02B6; //19200
// 	USART0_CTRLC = 0b10100111;  //8 bit mode
// 	PORTA_DIRSET = 0x01;
// 	USART0_CTRLB = 0b11000000;
// 	USART0_CTRLA = 0b10000000;


// 	ontvanger_buffer_uart0 = 0;

// 	//LED voor te testen 
// 	PORTC_DIR |= PIN7_bm;
	
// }

// ISR(USART0_RXC_vect){
// 	// PORTC_OUT |= PIN7_bm;
// 	// printf_P(PSTR("ontvanger interupt : "));
// 	// RX_inperupt_ontvanger();
// 	// PORTC_OUT &= ~PIN7_bm;
// 	 printf_P(PSTR("frame: %d \n\r"),USART0_RXDATAL);
// }



int main(void)
{
    //initialisatie 
    USART3_Init();
    initLedPoorten();
    initGlobalVariables();
    uarts_setup();
    
    //string in matrix zetten
    getUserInput();

    // CPU_SREG = 0b10000000;
    // uartsetup_ontvanger_uart0();

    while (1) 
    {
        printf_P(PSTR("ontvanger \n\r"));
        _delay_ms(10000);
    }
}
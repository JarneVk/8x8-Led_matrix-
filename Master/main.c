#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#include <stdio.h>
#include <avr/pgmspace.h>


// void uartsetup_zender_uart1(){
// 	printf_P(PSTR("init zender \n\r"));
// 	USART1_BAUD = 0x02B6; //19200
// 	USART1_CTRLC = 0b10100111;  //8 bit mode
// 	PORTC_DIRSET = 0x01;
// 	USART1_CTRLB = 0b01000000;
// 	USART1_CTRLA = 0b01000000;
		
// }

// void sendData_zender_usart1(uint8_t hexgetal){ 
// 	// USART1_CTRLB = 0b01000000;
// 	printf_P(PSTR("send %d \n\r"),hexgetal);
// 	zender_buffer_uart1 = hexgetal;
//     while(!(USART1_STATUS & USART_DREIF_bm));
//     USART1_TXDATAL = hexgetal;
// }

// ISR(USART1_TXC_vect){
//     printf_P(PSTR("tc \n\r"));
//     USART1_STATUS |= USART_TXCIF_bm;
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
    
    shiftTimer_setup();
    


    // CPU_SREG = 0b10000000;
    // uartsetup_zender_uart1();

    while (1) 
    {
        // USART1_TXDATAH = 0x01;
        // sendData_zender_usart1(60);  
        // _delay_ms(1000);
    }
}
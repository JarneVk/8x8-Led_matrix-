#include "../HeaderMatrix.h"
#include <avr/io.h>


void uarts_setup(){
    CPU_SREG = 0b10000000;
    TCA0_SINGLE_CTRLA = 0b00001111;
    uartsetup_zender_uart1();
    uartsetup_ontvanger_uart0();
}

// 1 voor ACK, 2 voor NACK, 3 voor EndOfMessage
int sendSpecial(int dat){
	if(USART0_STATUS&(1<<5)){		 // get de DREIF bit
		USART0_TXDATAH = 1;
		USART0_TXDATAL = dat;
        return 0;
    }    
    else {
        // register is nog niet geshift
        return 1;
    }
}
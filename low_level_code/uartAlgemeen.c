#include "../HeaderMatrix.h"
#include <avr/io.h>


void uarts_setup(){
    CPU_SREG = 0b10000000;
    TCA0_SINGLE_CTRLA = 0b00001111;
    uartsetup_zender_uart1();
    uartsetup_ontvanger_uart0();
}


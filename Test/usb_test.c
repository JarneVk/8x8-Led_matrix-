#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#ifdef PRINTFP
#include <stdio.h>
#endif

const char test[] PROGMEM = "test2\n\r";

int main(void){
    USART3_Init();
    // uint8_t i = 0;
    while(1){

        //printStringLiteral("test");
        // printf_P(PSTR("%d"),i);
        SRAM_printBytes((uint8_t*)stringfgColor, sizeof(stringfgColor));
        USART3_sendChar('\n');
        USART3_sendChar('\r');
        SRAM_printBytes((uint8_t*)stringbgColor, sizeof(stringbgColor));
        USART3_sendChar('\n');
        USART3_sendChar('\r');
        USART3_sendChar((char)0x03);
        _delay_ms(500);

        // int i = 0;
        // while(pgm_read_byte(&test[i]) != '\0'){
        //     USART3_printChar(pgm_read_byte(&test[i]));
        //     i++;
        // }
        // USART3_printChar('h');
        // USART3_printChar('a');
        // USART3_printChar('l');
        // USART3_printChar('l');
        // USART3_printChar('o');
        // USART3_printChar('\n');
        // USART3_printChar('\r');
        // i++;
        // _delay_ms(500);
    }
}
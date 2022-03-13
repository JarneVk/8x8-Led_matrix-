#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#ifdef PRINTFP
#include <stdio.h>
#endif

void USART3_sendChar(char data){
    while(!(USART3_STATUS & USART_DREIF_bm));
    USART3_TXDATAL = data;
}

#ifdef PRINTFP
static int USART3_printChar(char c,FILE *stream){
    USART3_sendChar(c);
    return 0;
}


static FILE USART3_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);
#endif
/*
Prints string from program memory to UART3
@param data: pointer to null terminated string in program memory
*/
void PROG_printString(const char data[]){
    while(pgm_read_byte(&data) != '\0'){
        USART3_sendChar(pgm_read_byte(&data));
        data++;
    }
}

void SRAM_printString(char data[]){
    while(*data != '\0'){
        USART3_sendChar(*data);
        data++;
    }
}

/*
Initialize USART3 for communication to host pc
*/
void USART3_Init(){
    cli();
    #ifdef PRINTFP
    stdout = &USART3_stream;
    #endif
    //9600
    USART3_BAUD = 0x056D;
    //Asynchronous even parity 1 stop bit 8 bit size
    USART3_CTRLC = 0b00100011;
    //PB0 as output
    PORTB_DIRSET = 0x01;
    //Enable transmitter and receiver
    USART3_CTRLB = 0b11000000;
    //Enable receive interrupt
    USART3_CTRLA = 0b10000000;

    sei();
 
}

//test
char input[MLENGTH + 1]; //+ 1 voor string termination
// char* inPointer = NULL;
uint8_t lengthIn = 0;
uint8_t index = 0;

ISR(USART3_RXC_vect){
     uint8_t inc = USART3_RXDATAL;
    if(inc != 3){
        if(index <= MLENGTH - 1){
            input[index] = inc;
            index++;
        }
    }else{
        input[index] = '\0';
        lengthIn = index;
        index = 0;
        SRAM_printString(input);
        USART3_sendChar((char)0x03);
    }
}

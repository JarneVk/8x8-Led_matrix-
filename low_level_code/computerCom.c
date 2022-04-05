#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#ifdef PRINTFP
#include <stdio.h>
#endif

/**
 * @brief print character function for general use.
 * 
 * @param data Character to be printed.
 */
void USART3_sendChar(char data){
    while(!(USART3_STATUS & USART_DREIF_bm));
    USART3_TXDATAL = data;
}

#ifdef PRINTFP
/**
 * @brief print character function used for printf family.
 * 
 * @param c 
 * @param stream 
 * @return int 
 */
static int USART3_printChar(char c,FILE *stream){
    USART3_sendChar(c);
    return 0;
}
static FILE USART3_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);
#endif

/**
 * @brief Prints string in program memory to usb port (USART3 port)
 * 
 * @param data: pointer to null terminated string in program memory
 */
void PROG_printString(const char data[]){
    while(pgm_read_byte(&data) != '\0'){
        USART3_sendChar(pgm_read_byte(&data));
        data++;
    }
}

/**
 * @brief Prints string in SRAM memory to usb port (USART3 port)
 * 
 * @param data: pointer to null terminated string in program memory
 */
void SRAM_printString(char data[]){
    while(*data != '\0'){
        USART3_sendChar(*data);
        data++;
    }
}

void SRAM_printBytes(uint8_t *data, uint8_t amount){
    for(int i = 0; i < amount; i++){
        printf_P(PSTR("%x"),*(data + i));
    }
}

/**
 * @brief Initliaze USART3 for communication with computer.
 * 9600 baudrate even parity 1 stop bit
 * 
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
// char inputString[MAX_STRING_LEN];
// Led stringColor[MAX_MESSAGE_COLORS];
// uint8_t colorIndex[MAX_MESSAGE_COLORS];
// // char* inPointer = NULL;
uint8_t lengthInputString = 0;
uint8_t indexIn = 0;
uint8_t sendPhase = 0;

ISR(USART3_RXC_vect){
     uint8_t inc = USART3_RXDATAL;
    if(inc == 1){
        sendPhase = 0;
        indexIn = 0;
    }else{
        switch(sendPhase){
            case 0:
                if(inc != 3){
                    if(indexIn <= MAX_STRING_LEN - 2){ // -2 voor string termination
                        inputString[indexIn] = inc;
                        indexIn++;
                    }
                }else{
                    inputString[indexIn] = '\0';
                    lengthInputString = indexIn;
                    indexIn = 0;
                    sendPhase++;
                } break;
            case 1:
            case 2:
                if(inc != 3){
                    if(indexIn <= MAX_MESSAGE_COLORS - 1){
                        if(sendPhase == 1){
                            stringColor[indexIn].brightness = ((inc>>4) & 0x0f);
                            stringColor[indexIn].red = (inc<<4) & 0xf0;
                            sendPhase++;
                        }else{
                            stringColor[indexIn].blue = (inc>>4) & 0x0f;
                            stringColor[indexIn].green = (inc<<4) & 0xf0;
                            indexIn++;
                            sendPhase--;
                        }
                    }
                }else{
                    indexIn = 0;
                    sendPhase += 2;
                } break;
            case 3:
                if(inc != 3){
                    if(indexIn <= MAX_MESSAGE_COLORS - 1){
                        colorIndex[indexIn] = inc;
                    }
                }else{
                    indexIn = 0;
                    sendPhase = 0;
                } break;
        }
    }
}

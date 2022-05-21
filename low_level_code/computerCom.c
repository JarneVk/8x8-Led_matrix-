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
 * @brief Initliaze USART3 for communication with computer.
 * 9600 baudrate even parity 1 stop bit
 * when PRINTFP is defined the printf family will print to usart3
 */
void USART3_Init(){
    cli();
    #ifdef PRINTFP
    stdout = &USART3_stream;
    #endif
    CPUINT_LVL1VEC = USART3_RXC_vect_num;//tesster tesst test test test
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

Led inputLogo[8][8];
void sendReceivedData(){
    USART3_sendChar((char)0x01);

    uint8_t lengte = 0;
    while(inputString[lengte] != '\0'){
        USART3_sendChar(inputString[lengte++]);
    }
    USART3_sendChar((char)0x03);
    //eind ascii
    USART3_sendChar(input_brightness <<4 | input_red[0]);
    USART3_sendChar(input_green[0] << 4 | input_blue[0]);
    for(int i = 1; i < lengte; i++){
        USART3_sendChar(input_red[i]);
        USART3_sendChar(input_green[i] << 4 | input_blue[i]);
    }

    for(int i = 0; i < lengte; i++){
        USART3_sendChar(input_bgred[i]);
        USART3_sendChar(input_bggreen[i] << 4 | input_bgblue[i]);
    }
    //logo
    for(int i = 0; i < AMOUNT; i++){
        for(int j = 0; j < AMOUNT; j++){
            USART3_sendChar(inputLogo[i][j].red);
            USART3_sendChar(inputLogo[i][j].green << 4 | inputLogo[i][j].blue);
        }
    }
}


uint8_t lengthInputString = 0;
uint8_t indexIn = 0;
uint8_t indexJn = 0;
uint8_t sendPhase = 0;
uint8_t inputLength = 0;



ISR(USART3_RXC_vect){
    uint8_t inc = USART3_RXDATAL;

    switch(sendPhase){
        case 0:
            if(inc == 1){
                sendPhase = 1;
                indexIn = 0;//redundant
                indexJn = 0;//redundant
            }break;
        case 1:
            //Receive message
            if(inc != 3){
                if(indexIn <= MAX_STRING_LEN){ // geen -1 voor string termination
                    inputString[indexIn] = inc;
                    indexIn++;
                }
            }else{
                inputString[indexIn] = '\0';
                lengthInputString = indexIn;
                inputLength = indexIn;
                indexIn = 0;
                sendPhase = 2;
            } break;
            //eind ascii
        case 2:
            //aparte case voor eerste kleur sinds brightness alleen hier bij staat
            input_brightness = ((inc>>4) & 0x0f);
            input_red[indexIn] = (inc) & 0x0f;
            sendPhase = 4;//naar 4 omdat volgende frame groen en blauw bevat
            break;
        case 3:
        case 4:
            if(sendPhase == 3){
                input_red[indexIn] = (inc) & 0x0f;
                sendPhase++;
            }else{
                input_green[indexIn] = (inc>>4) & 0x0f;
                input_blue[indexIn] = (inc) & 0x0f;
                indexIn++;
                sendPhase--;
            }
            if(indexIn >= inputLength){
                indexIn = 0;
                sendPhase = 5;
            } break;
        case 5:
        case 6:
            //niet geimplmenteerde background
            if(sendPhase == 5){
                input_bgred[indexIn] = (inc) & 0x0f;
                sendPhase++;
            }else{
                input_bggreen[indexIn] = (inc>>4) & 0x0f;
                input_bgblue[indexIn] = (inc) & 0x0f;
                indexIn++;
                sendPhase--;
            }
            if(indexIn >= inputLength){
                indexIn = 0;
                sendPhase = 7;
            } break;
        case 7:
        case 8:
            //inlezen logo
            if(sendPhase == 7){
                inputLogo[indexIn][indexJn].red = inc & 0x0f;
                inputLogo[indexIn][indexJn].brightness = input_brightness;//kopieren brightness voor HL.c
                sendPhase++;
            }else{
                inputLogo[indexIn][indexJn].green = (inc>>4) & 0x0f;
                inputLogo[indexIn][indexJn].blue = inc & 0x0f;
                indexJn++;
                if(indexJn == 8){
                    indexJn = 0;
                    indexIn++;
                }
                
                sendPhase--;
            }
            if(indexIn == 8){
                sendReceivedData();
                indexIn = 0;
                indexJn = 0;
                sendPhase = 9;
            }break;
        case 9:
                if(inc > 0x7E){
                    writeToEeprom(inputString, input_red, input_green, input_blue, inputLogo, input_brightness);
                    getUserInput(inputString, input_red, input_blue, input_green, input_brightness);
                    getUserLogo(inputLogo);
                }
            sendPhase = 0;
            break;
    }
    
}

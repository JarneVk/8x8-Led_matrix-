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

    TCB2_CCMPL = 0x00;
	TCB2_CCMPH = 0x30;
	TCB2_CTRLA = 0b00000101; 
	TCB2_CTRLB = 0x01;		//periotic interupt
	TCB2_INTCTRL = 0x01;	//enable inetrups

    sei();
 
}

// Led (*inputLogo)[8][8] = NULL;
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

    // USART3_sendChar((char)0x03);
    for(int i = 0; i < lengte; i++){
        USART3_sendChar(input_bgred[i]);
        USART3_sendChar(input_bggreen[i] << 4 | input_bgblue[i]);
    }
    // USART3_sendChar((char)0x03);
    //logo
    for(int i = 0; i < AMOUNT; i++){
        for(int j = 0; j < AMOUNT; j++){
            // USART3_sendChar(inputLogo[i][j]->red);
            // USART3_sendChar(inputLogo[i][j]->green << 4 | inputLogo[i][j]->blue);
            USART3_sendChar(inputLogo[i][j].red);
            USART3_sendChar(inputLogo[i][j].green << 4 | inputLogo[i][j].blue);
        }
    }
    // // USART3_sendChar((char)0x03);
    // USART3_sendChar((char)0x03);
    // USART3_sendChar((char)0x03);
}


uint8_t lengthInputString = 0;
uint8_t indexIn = 0;
uint8_t indexJn = 0;
uint8_t sendPhase = 0;
uint8_t inputLength = 0;



ISR(USART3_RXC_vect){
    uint8_t inc = USART3_RXDATAL;
    // USART3_sendChar(sendPhase);

    switch(sendPhase){
        case 0:
            if(inc == 1){
                // USART3_sendChar(8);
                // USART3_sendChar(inc);
                // USART3_sendChar((char)0x03);
                sendPhase = 1;
                indexIn = 0;
                indexJn = 0;
                // if(inputLogo == NULL)
                //     inputLogo = malloc(sizeof(Led)*AMOUNT*AMOUNT);
            }break;
        case 1:
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
            input_brightness = ((inc>>4) & 0x0f);
            input_red[indexIn] = (inc) & 0x0f;
            sendPhase = 4;
            break;
        case 3:
        case 4:
            // if(inc != 3){
            
            if(sendPhase == 3){
                input_red[indexIn] = (inc) & 0x0f;
                sendPhase++;
            }else{
                input_green[indexIn] = (inc>>4) & 0x0f;
                input_blue[indexIn] = (inc) & 0x0f;
                indexIn++;
                sendPhase--;
            }
                // USART3_sendChar(indexIn);
                // }
            if(indexIn >= inputLength){
                indexIn = 0;
                sendPhase = 5;
            } break;
        case 5:
        case 6:
            if(sendPhase == 5){
                input_bgred[indexIn] = (inc) & 0x0f;
                sendPhase++;
            }else{
                input_bggreen[indexIn] = (inc>>4) & 0x0f;
                input_bgblue[indexIn] = (inc) & 0x0f;
                indexIn++;
                sendPhase--;
            }
                // USART3_sendChar(indexIn);
            if(indexIn >= inputLength){
                indexIn = 0;
                sendPhase = 7;
            } break;
        case 7:
        case 8:
            
            if(sendPhase == 7){
                // inputLogo[indexIn][indexJn]->red = inc & 0x0f;
                inputLogo[indexIn][indexJn].red = inc & 0x0f;
                // USART3_sendChar(indexIn);
                // USART3_sendChar(indexJn);
                // USART3_sendChar(0xFF);
                sendPhase++;
            }else{
                // inputLogo[indexIn][indexJn]->green = (inc>>4) & 0x0f;
                // inputLogo[indexIn][indexJn]->blue = inc & 0x0f;
                inputLogo[indexIn][indexJn].green = (inc>>4) & 0x0f;
                inputLogo[indexIn][indexJn].blue = inc & 0x0f;
                // USART3_sendChar(indexJn);
                indexJn++;
                if(indexJn == 8){
                    indexJn = 0;
                    indexIn++;
                }
                
                sendPhase--;
            }
            //logo
            if(indexIn == 8){
                sendReceivedData();
                
                indexIn = 0;
                indexJn = 0;
                sendPhase = 9;
            }break;
        case 9:
            // USART3_sendChar(8);
            // USART3_sendChar(inc);
            // USART3_sendChar((char)0x03);

                // USART3_sendChar(inc);
                // USART3_sendChar((char)0x03);
                if(inc > 0x7E){
                    // USART3_sendChar('k');
                    // USART3_sendChar((char)0x03);
                    getUserInput(inputString, input_red, input_blue, input_green, input_brightness);
                    writeToEeprom(inputString, input_red, input_green, input_blue, inputLogo, input_brightness);
                }
            
            // free(inputLogo);
            // inputLogo = NULL;
            sendPhase = 0;
            break;
    }
    
}

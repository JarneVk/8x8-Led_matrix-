#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#ifdef PRINTFP
#include <stdio.h>
#endif


int main(void){
    USART3_Init();
    // uint8_t i = 0;
    Led inputLogo[8][8];
    while(1){

        readFromEeprom(inputString, input_red, input_green, input_blue, inputLogo, &input_brightness);
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
                // USART3_sendChar(inputLogo[i][j]->red);
                // USART3_sendChar(inputLogo[i][j]->green << 4 | inputLogo[i][j]->blue);
                USART3_sendChar(inputLogo[i][j].red);
                USART3_sendChar(inputLogo[i][j].green << 4 | inputLogo[i][j].blue);
            }
        }
        _delay_ms(5000);
    }
}
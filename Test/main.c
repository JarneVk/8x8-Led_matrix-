#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/pgmspace.h>

int main(void)
{   
    USART3_Init();
    
    initLedPoorten();
    uarts_setup();
    //leds testing 
    /*
    while(1){
        uint32_t array[64];
        for(int i=0; i<64;i++){
            array[i] = 0b11100001000011110000000011111111;
            writeToLed(array);
            _delay_ms(200);
        }
        for(int i=63; i>=0;i--){
            array[i] = 0b11100000000000000000000000000000;
            writeToLed(array);
            _delay_ms(200);
        }
    }

    */
    //uart zender testing 
    shiftTimer_setup();
    
    //uart ontvanger (hier niets voor doen)
    while (1)
    {       

        //printf_P(PSTR("test"));
        // laat de interups werken
    }
    



}



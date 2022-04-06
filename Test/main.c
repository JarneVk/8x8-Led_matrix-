#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // initLedPoorten();
    uarts_setup();
    //leds testing 
    /*
    while(1){
        uint32_t array[8] = {0,0,0,0,0,0,0,0};
        for(int i=0; i<8;i++){
            array[i] = 0b11100111111111111111111111111111;
            writeToLed(array);
            _delay_ms(1000);
        }
        for(int i=7; i>=0;i--){
            array[i] = 0b11100000000000000000000000000000;
            writeToLed(array);
            _delay_ms(1000);
        }
    }

    */
    //uart zender testing 
    // shiftTimer_setup();

    //uart ontvanger (hier niets voor doen)
    while (1)
    {       
        // laat de interups werken
    }
    



}



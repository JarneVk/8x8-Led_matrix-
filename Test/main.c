#include "../HeaderMatrix.h"
#include <avr/io.h>



int main(void)
{
    
    initLedPoorten();
    uartsetup_zender_uart1();
    uartsetup_ontvanger_uart0();
    /*leds testing 
    
    while(1){
        uint32_t array[8] = {0,0,0,0,0,0,0,0};
        for(int i=0; i<7;++i){
            array[i] = 1;
            writeToLed(array);
        }
    }
    */


    //uart zender testing 
    shiftTimer_setup();

    //uart ontvanger (hier niets voor doen)
    



}



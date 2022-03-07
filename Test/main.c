#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
    
    initLedPoorten();
    //uartsetup_zender_uart1();
    //uartsetup_ontvanger_uart0();
    //leds testing 
    
    while(1){
        uint32_t array[8] = {0,0,0,0,0,0,0,0};
        for(int i=0; i<8;i++){
            array[i] = 1;
            writeToLed(array);
        }
        _delay_ms(1000);
    }


    //uart zender testing 
    //shiftTimer_setup();

    //uart ontvanger (hier niets voor doen)
    



}



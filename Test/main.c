#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

int main(void)
{   
    CPU_SREG = 0b10000000;
    TCA0_SINGLE_CTRLA = 0b00001111;
    USART3_Init();
    zender_timer_setup();
    PORTC_DIR |= PIN5_bm;
    PORTC_DIR |= PIN4_bm;

    while (1)
    {   
        PORTA_OUT |= PIN3_bm;
        if(TCB1_STATUS = 0x01){
            PORTC_OUT |= PIN4_bm;
            printf_P(PSTR("%d %d \n\r"),TCB1_CNTH,TCB1_CNTL);
        }
        _delay_ms(200);
        
        // laat de interups werken
    }


}



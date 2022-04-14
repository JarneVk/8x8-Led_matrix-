#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

int main(void)
{   
    CPU_SREG = 0b10000000;
    
    USART3_Init();
    zender_timer_setup();
    PORTC_DIR |= PIN5_bm;
    PORTC_DIR |= PIN4_bm;

    while (1)
    {   
        if(TCB1_STATUS = 0x01){
            PORTC_OUT |= PIN4_bm;
            printf_P(PSTR("%d %d \n\r"),TCB1_CNTH,TCB1_CNTL);
        }
        _delay_ms(5000);
        // laat de interups werken
    }
    

}



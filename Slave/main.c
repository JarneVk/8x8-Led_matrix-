#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    master = 0;
    //initialisatie 
    USART3_Init();
    initLedPoorten();
    initGlobalVariables();
    uarts_setup();
    //shiftTimer_setup();
    //string in matrix zetten
    // getUserInput();
    
    while (1) 
    {
		
    }
}
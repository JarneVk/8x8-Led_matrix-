#include "../HeaderMatrix.h"
#include <avr/io.h>

int main(void)
{
    master = 1;
    //initialisatie 
    USART3_Init();
    initLedPoorten();
    initGlobalVariables();
    uarts_setup();
    
    //string in matrix zetten
    // getUserInput();
    
    shiftTimer_setup();
    
    while (1) 
    {
		
    }
}
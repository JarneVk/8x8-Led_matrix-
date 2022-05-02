#include "../HeaderMatrix.h"
#include <avr/io.h>



int main(void)
{
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
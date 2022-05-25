#include "../HeaderMatrix.h"
#include <avr/io.h>

int main(void)
{
    master = 1;
    //initialisatie 
    USART3_Init();
    initLedPoorten();
    initGlobalVariables();
    Led inputLogo[8][8];
    if(readFromEeprom(inputString, input_red, input_green, input_blue, inputLogo, &input_brightness)){
        // readFromEeprom(inputString, input_red, input_green, input_blue, inputLogo, &input_brightness);
        getUserInput(inputString, input_red, input_blue, input_green, input_brightness);
        getUserLogo(inputLogo);
    }

    uarts_setup();
    
    //string in matrix zetten
    // getUserInput();
    
    shiftTimer_setup();
    
    while (1) 
    {
		
    }
}
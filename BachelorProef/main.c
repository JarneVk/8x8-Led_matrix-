/*
 * BachelorProef.c
 *
 * Created: 21/02/2022 15:52:56
 * Author : Gebruiker
 */ 

#include "HeaderMatrix.h"
#include <avr/io.h>



int main(void)
{
	#ifdef SLAVE
	uartsetup();
	
	readRegister_usart0();
	#endif
    /* Replace with your application code */
    while (1) 
    {
		
    }
}


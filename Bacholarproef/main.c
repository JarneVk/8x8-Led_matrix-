/*
 * Bacholarproef.c
 *
 * Created: 21/02/2022 15:01:44
 * Author : Gebruiker
 */ 

#include <avr/io.h>



void togleBit(uint8_t* registerByte,uint8_t bit){    // registerByte is het rester waarin de bit zich bevind
	*registerByte ^= (1<<bit);       // bit is de bit (vaak de difine) die je wilt toggelen
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}


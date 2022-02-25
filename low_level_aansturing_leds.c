/*
aansturing Leds : APA102
	-beginnen met een start frame van 32 keer 0 -> 4 bytes van 0
	-De LED frames, hoe meer led frames achtereen hoe verder het zal doorschuiven in 1 verzending 
	-Een LED frame -> 3bit van 1, 5 bits global, 8bit Blue, 8bit Green, 8bit Red	=> de global bit zorgt voor de brightness
	-End frame : 32 bit 1, 4x bits van 1

    op de pin PB5 staat de output die gekoppeld moet worden aan SDI van de apa102 
*/

#include <avr/io.h>
#include "HeaderMatrix.h"

void initLedPoorten(){
    //initialisatie van de gebruikte poorten (als output zetten)
    PORTB_DIR |= PIN5_bm;   // pin5_bm is een standaard bitmap functie van avr/io

}


int writeToLed(char bitArray[],int aantalAangestuurdeLeds){

    for(int i=0; i<32; ++i){    //32x0
        PORTB_OUT &= ~PIN5_bm;
    }
    for(int i=0; i<aantalAangestuurdeLeds;++i){             // led info doorsturen
        for(int j=0; j<29;++j){
            if(bitArray[(aantalAangestuurdeLeds*29)+j]){
                PORTB_OUT |= PIN5_bm;
            }
            else{
                PORTB_OUT &= ~PIN5_bm;
            }
        }
    }

    for(int i=0; i<32; ++i){    //32x1
        PORTB_OUT |= PIN5_bm;
    }

}



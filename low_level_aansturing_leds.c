/*
aansturing Leds : APA102
	-beginnen met een start frame van 32 keer 0 -> 4 bytes van 0
	-De LED frames, hoe meer led frames achtereen hoe verder het zal doorschuiven in 1 verzending 
	-Een LED frame -> 3bit van 1, 5 bits global, 8bit Blue, 8bit Green, 8bit Red	=> de global bit zorgt voor de brightness
	-End frame : 32 bit 1, 4x bits van 1
*/

#include <avr/io.h>
#include "HeaderMatrix.h"

void initLedPoorten(){
    //initialisatie van de gebruikte poorten (als output zetten)
}


int writeToLed(&bitArray[29]){




}



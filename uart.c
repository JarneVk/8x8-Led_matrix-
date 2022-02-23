/*
 * uart.c
 *
 * Created: 21/02/2022 16:03:28
 *  Author: Gebruiker
 */ 
/*
 * GccApplication1.c
 *
 * Created: 21/02/2022 13:47:48
 * Author : Gebruiker
 */ 

// In dit programma confirureren we de uart poorten voor communicatie
// en functies voor het in en uitlezen van de Rx en Tx poorten



#include "HeaderMatrix.h"
#include <avr/io.h>

#define NAME3(a,b,c)         NAME3_HIDDEN(a,b,c)
#define NAME3_HIDDEN(a,b,c)  a ## b ## c

#define initIrcomUsart(ARG) \
NAME3(USART,ARG,_BAUDL) = 0xB6;\
NAME3(USART,ARG,_BAUDH) = 0x02;\
NAME3(USART,ARG,_CTRLC) = 0x3E;  //00111110 -> 9bit verzending


void uartsetup(){
	initIrcomUsart(0);
	PORTA_DIRSET = 0x01;
	USART0_CTRLB = 0xC0;
	
	initIrcomUsart(1);
	PORTC_DIRSET = 0x01;
	USART1_CTRLB = 0xC0;	
}


/* samenhang van verzenden en ontvangen -> Status register */

/* send data : we kiezen voor 8 bit verzending -> CHSIZE in Control C moet op 8 bit staan
    als er data in TXDATAL word geschreven zal deze in de TX buffer komen en serieel worden doorgestuurd
    je kan ENKEL in het register schrijven als DREIF (in usartn.status) bit op 1 staat
*/

int sendData_usart0(int hexgetal){   // returnt een 0 als het kan verzonden zorden anders een 1
    if(USART0_STATUS&(1<<5)){  // get de DREIF bit
		USART0_TXDATAH &= ~(1<<0);	// zet bit op 0
        USART0_TXDATAL = hexgetal;
        return 0;
    }    
    else {
        // register is nog niet geshift > even wachten
        return 1;
    }
}

int sendACK_usart0(){
	if(USART0_STATUS&(1<<5)){  // get de DREIF bit
		USART0_TXDATAH &= ~(1<<0);	// zet bit op 0
		USART0_TXDATAL = 0x00;
		return 0;
	}
	else {
		return 1;
	}
}

int sendNACK_usart0(){
	if(USART0_STATUS&(1<<5)){  // get de DREIF bit
		USART0_TXDATAH |= (1<<0);	// zet bit op 1
		USART0_TXDATAL = 0xFF;
		return 0;
	}
	else {
		return 1;
	}
}

/* get data : in RXDATAH, bit 7 zegt of er data in de buffer zit -> eerste hiernaar kijken 
    als RXDATAH of L worden gelezen zal de buffer doorschuiven (afhankelijk van de configuratie in Control C)
    => eerst het niet schiftende register uitlezen en dan het schiftende 
    #optioneel FERR geef aan of de frame juist is toegekomen#
    #PERR parity check, een foute controle op de data #

    aanpak? 
    - eerste RXDATAH inlezen en kijken of er nieuwe data aanwezig is 
    - checken of de data goed is toegekomen met PERR/FERR
    - als alles correct is -> RXDATAL inlezen en register laten schiften
*/

int readRegister_usart0(){      // geeft 8 bits terug + 1 bit als packetnummer 
	int bits[2];
	if(USART0_RXDATAH&(1<<7)){	// kijken naar 7de bit
		bits[0] = USART0_RXDATAH;
		bits[1] = USART0_RXDATAL; 
		
		if(bits[0]&(1<<2) || bits[0]&(1<<1)){	// kijken of er geen frame of parity errors zijn
			sendNACK_usart0();			// 0xAA voorlopig als NACK
			return 1;
		}else{//else if checken op NACK moet nog worden toegevoegd -> vraag hoe gaan we dit naar buiten brengen via de int?
			sendACK_usart0();
			return bits[1];
		}	
	}
	else{
		return 1;	// nog geen data beschikbaar
	}
}





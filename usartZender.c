/*
 * uartZender.c
 *
 * Created: 21/02/2022 16:03:28
 *  Author: Gebruiker
 */ 
 

/*
usartZender zorgt voor de low level aansturen van de usart poorten die aan de IRED trancievers worden gekoppeld

de Zender zal werken volgens een sliding window met buffer 1, en werkt in 1 richting 
het zal dus enkel een ACK(packet) of NACK(packet) kunnen ontvangen 

het stuurt een packet_nummer + 8bit info

bij binnenkomen van een NACK zal het het juiste packet herzenden 
bij ACK zal het dit packet van de buffer terug vrijgeven
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "HeaderMatrix.h"

#define NAME3(a,b,c)         NAME3_HIDDEN(a,b,c)
#define NAME3_HIDDEN(a,b,c)  a ## b ## c

#define initIrcomUsart(ARG) \
NAME3(USART,ARG,_BAUDL) = 0xB6;\
NAME3(USART,ARG,_BAUDH) = 0x02;\
NAME3(USART,ARG,_CTRLC) = 0x3E;  //00111110 -> 9bit verzending


void uartsetup_zender_uart1(){
	initIrcomUsart(1);
	PORTA_DIRSET = 0x01;
	USART1_CTRLB = 0xC0;
	
	initIrcomUsart(1);
	PORTC_DIRSET = 0x01;
	USART1_CTRLB = 0xC0;

	zender_buffer_uart1 = 0;
	zender_verbinding = 0;
		
}


/* SendData : de ontvanger zal een ACK(frame) een NACK(frame) kunnen sturen naar de zender
		ACK :   1 0000 0001
		NACK :	1 0000 0010
		verbinding request : 0 1010 1010 => 0xAA

 */

/* send data : we kiezen voor 8 bit verzending -> CHSIZE in Control C moet op 8 bit staan
    als er data in TXDATAL word geschreven zal deze in de TX buffer komen en serieel worden doorgestuurd
    je kan ENKEL in het register schrijven als DREIF (in usartn.status) bit op 1 staat
*/

int sendData_zender_usart1(int hexgetal){   // returnt een 0 als het kan verzonden zorden anders een 1

	zender_buffer_uart1 = hexgetal;
    if(USART1_STATUS&(1<<5)){  // get de DREIF bit
        USART1_TXDATAL = hexgetal;
        return 0;
    }    
    else {
        // register is nog niet geshift > even wachten
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

void interup_ReadData(){
	int bits[2];
	if(USART1_RXDATAH&(1<<7)){	// kijken naar 7de bit
		bits[0] = USART1_RXDATAH;
		bits[1] = USART1_RXDATAL; 
		
		if(bits[0]&(1<<2) || bits[0]&(1<<1)){	// kijken of er geen frame of parity errors zijn
			//NACK sturen 		
			//of negeer het en wat op de timeout van de Ontvanger
		}else if(bits[0]==1 && bits[1]&(1<<2)){	//als een NACK tokomt
			while(sendData_zender_usart1(zender_buffer_uart1)){
				_delay_ms(1);
			}
		}else if(bits[0]==1 && bits[1]==1){		//ACK nieuw packetje sturen
			while(sendData_zender_usart1(1)){		//1 vevangen door getNewData()
				_delay_ms(1);
			}	
		}
		else if(bits[1]== 0b10101010){		//new verbinding request
			connectRequest();
		}	
	}
}

void connectRequest(){
	sendData_zender_usart1(1);

	// nieuwe matrix doorsturen 	
	
}



ISR(USART1_RXC_vect){			//interupt register 
	if(zender_verbinding == 1){
		interup_ReadData();
	}
	else{
		connectRequest();
	}
}





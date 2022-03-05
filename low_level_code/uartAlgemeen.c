#include "../HeaderMatrix.h"
#include <avr/io.h>


// 1 voor ACK, 2 voor NACK, 3 voor EndOfMessage
int sendSpecial(int dat){
	if(USART0_STATUS&(1<<5)){		 // get de DREIF bit
		USART0_TXDATAH = 1;
		USART0_TXDATAL = dat;
        return 0;
    }    
    else {
        // register is nog niet geshift
        return 1;
    }
}
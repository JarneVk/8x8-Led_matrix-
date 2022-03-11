#include "../HeaderMatrix.h"
#include <avr/io.h>
#include <avr/pgmspace.h>


void USART3_printChar(char data){
    while(!(USART3_STATUS & USART_DREIF_bm));
    USART3_TXDATAL = data;

}


/*
Prints string from program memory to UART3
@param data: pointer to null terminated string in program memory
*/
void PROG_printString(const char data[]){
    int i = 0;
    while(pgm_read_byte(&data[i]) != '\0'){
        USART3_printChar(pgm_read_byte(&data[i]));
        i++;
    }
}

/*
Initialize USART3 for communication to host pc
*/
void USART3_Init(){

    //9600
    USART3_BAUD = 0x056D;
    //Asynchronous even parity 1 stop bit 8 bit size
    USART3_CTRLC = 0b00100011;
    //PB0 as output
    PORTB_DIRSET = 0x01;
    //Enable transmitter and receiver
    USART3_CTRLB = 0b11000000; 
}





/*ISR(USART3_RCX){

    receivedData = malloc(sizeof(uint8_t));



    free(receivedData);
    receivedData = 0;
}*/

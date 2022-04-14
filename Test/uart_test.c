//uart zender testing
#include <avr/io.h>
#include <avr/pgmspace.h>
#include<stdio.h>
#include "../HeaderMatrix.h"


//static int packetje=0; 
/*
uint8_t getNextOutputData(){
   return 0b11101010;
}*/

//uart ontvanger testing 
/*
static uint8_t array_ont[16];
int writeOntvangenData(uint8_t data){
    if(ontvang_i>16){
        return 1;
    } else  {
        array_ont[ontvang_i] = data;
        ontvang_i ++;
        return 0;
    }
}
*/
/*
void ledsAansturen(){
    static uint32_t newArray[8];
    int z = 0;
    for(int m=0;m<8;++m){
        newArray[m] = ((uint32_t)array_ont[z]<<24) + ((uint32_t)array_ont[z+1]<<16) + ((uint32_t)array_ont[z+2]<<8) + (uint32_t)array_ont[z+3];
        z+=4;
    }
    for (int i = 0; i < 8; i++)
    {
        printf_P(PSTR("[%d]"),newArray[i]);
    }
    //writeToLed(newArray);
}
*/



//uart zender testing
#include <avr/io.h>
#include "../HeaderMatrix.h"

static uint32_t array[8] = {0,0,0,0,0,0,0,0};
static int packetje=0; 

uint8_t getNextOutputData(){
    /*
    uint32_t var =0 ;
    if(part==0){
        var =  array[packetje]>>24;
    }
    else if(part==1){
        var = array[packetje]>>16;
    }
    else if(part==2){
        var = array[packetje]>>8;
    }
    else {
        part = 0;
        var = array[packetje];
        if(packetje<7){
        ++packetje;
    }
    }
    return (uint8_t)var;
    */
   return 0b11111111;
}
static int m_shift=0;
void shift_matrix(){
    /*
    part = 0;
    packetje=0;
    array[m_shift] = 0b11100111111111111111111111111111;
    if(m_shift<7){
        m_shift++;
    }
    else{
        for(int i=0; i<8; i++){
            array[i] = 0b11100000000000000000000000000000;
        }
        m_shift=0;
    }
    SendNewColumn();
    */
}



//uart ontvanger testing 
static int ontvang_i=0;
static uint8_t array_ont[32];
int writeOntvangenData(uint8_t data){
    array_ont[ontvang_i] = data;
    if(ontvang_i>=32){
        ontvang_i++;
        return 1;
    }
    else{
        ontvang_i =0;
        return 0;
    }  
}

void ledsAansturen(){
    static uint32_t newArray[8];
    int z = 0;
    for(int m=0;m<8;++m){
        newArray[m] = ((uint32_t)array_ont[z]<<24) + ((uint32_t)array_ont[z+1]<<16) + ((uint32_t)array_ont[z+2]<<8) + (uint32_t)array_ont[z+3];
        z+=4;
    }
    writeToLed(newArray);
}



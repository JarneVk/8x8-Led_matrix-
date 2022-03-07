//uart zender testing
#include <avr/io.h>
#include "../HeaderMatrix.h"

static uint32_t array[8] = {0,0,0,0,0,0,0,0};
static int packetje=0; 

uint8_t getNextOutputData_zender(){
    uint8_t var = array[packetje];
    if(packetje<7){
        ++packetje;
    }
    return var;
}
static int m_shift=0;
void shift_matrix(){
    packetje=0;
    array[m_shift] = 1;
    if(m_shift<7){
        shiftTimer_reset();
        ++m_shift;
    }
    else{
        m_shift=0;
    }
    SendNewColumn();
}



//uart ontvanger testing 
static int ontvang_i=0;
static uint8_t array_ont[32];
int writeOntvangenData_test(uint8_t data){
    array_ont[ontvang_i] = data;
    if(ontvang_i>=32){
        return 1;
    }
    else{
        return 0;
    }  
}

void ledsAansturen_test(){
    static uint32_t newArray[8];
    int z = 0;
    for(int m=0;m<8;++m){
        newArray[m] = (array_ont[z]<<24) + (array_ont[z+1]<<16) + (array_ont[z+2]<<8) + array_ont[z+3];
        z+=4;
    }
    writeToLed(newArray);
}



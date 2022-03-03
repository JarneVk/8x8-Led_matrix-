//uart zender testing
#include <avr/io.h>

uint32_t array[8] = {0,0,0,0,0,0,0,0};
int j=0; 

uint8_t getNextOutputData(){
    uint8_t var = array[j];
    if(j<7){
        ++j;
    }
    return var;
}
int k=0;
void shift_interupt_test(){
    j=0;
    array[k] = 1;
    if(k<7){
        shiftTimer_reset();
        ++k;
    }
    else{
        k=0;
    }
    SendNewColumn();
}



//uart ontvanger testing 
int i=0;
uint8_t array_ont[32];
int writeOntvangenData(uint8_t data){
    array_ont[i] = data;
    if(i>=32){
        return 1;
    }
    else{
        return 0;
    }  
}

void ledsAansturenTest(){
    uint32_t newArray[8];
    int z = 0;
    for(int m=0;m<8;++m){
        uint32_t newArray[m] = (array_ont[z]<<24) + (array_ont[z+1]<<16) + (array_ont[z+2]<<8) + array_ont[z+3];
        z+=4;
    }
    writeToLed(newArray);
}



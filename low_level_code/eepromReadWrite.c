#include "HeaderMatrix.h"
#include <avr/eeprom.h>


void writeToEeprom(char message[], uint8_t s_r[], uint8_t s_g[], uint8_t s_b[], Led logo[], uint8_t brightness){
    eeprom_busy_wait();
    uint8_t messageLength = 0;
    uint8_t currentAddres = 0;
    for(; message[messageLength] != '\0'; messageLength++);
    
    uint8_t uneven = messageLength%2;

    eeprom_update_byte(currentAddres++, 1); //data is in eeprom

    for(int i = 0; i < messageLength; i++){
        eeprom_update_byte(currentAddres++, message[i]);
    }

    for(int i = 0; i < messageLength; i+=2){
        if((i+1) < messageLength)
            eeprom_update_byte(currentAddres++, ((s_r[i] << 4) & 0xf0) | s_r[i+1]);
        else
            eeprom_update_byte(currentAddres++, ((s_r[i] << 4) & 0xf0) | s_g[0]);
    }

    for(int i = uneven; i < messageLength; i+=2){
        if((i+1) < messageLength)
            eeprom_update_byte(currentAddres++, ((s_g[i] << 4) & 0xf0) | s_g[i+1]);
        else
            eeprom_update_byte(currentAddres++, ((s_g[i] << 4) & 0xf0) | s_b[0]);
    }

    for(int i = 0; i < messageLength; i+=2){
        if((i+1) < messageLength)
            eeprom_update_byte(currentAddres++, ((s_b[i] << 4) & 0xf0) | s_b[i+1]);
        else
            eeprom_update_byte(currentAddres++, (s_b[i] << 4) & 0xf0);
    }

    for(int i = 0; i < AMOUNT; i+=2){
        for(int j = 0; j < AMOUNT; j+=2){
            eeprom_update_byte(currentAddres++, ((logo[i].red << 4) & 0xf0) | logo[i].blue);
            eeprom_update_byte(currentAddres++, ((logo[i].green << 4) & 0xf0) | logo[i+1].red);
            eeprom_update_byte(currentAddres++, ((logo[i+1].blue << 4) & 0xf0) | logo[i+1].green);
        }
    }
}
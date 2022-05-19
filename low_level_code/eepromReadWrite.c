#include "../HeaderMatrix.h"
#include <avr/eeprom.h>


void writeToEeprom(char message[], uint8_t s_r[], uint8_t s_g[], uint8_t s_b[], Led logo[][AMOUNT], uint8_t brightness){
    uint8_t messageLength = 0;
    uint8_t currentAddres = 0;
    //length of message
    for(; message[messageLength] != '\0'; messageLength++);
    messageLength++;
    uint8_t uneven = messageLength%2;

    eeprom_update_byte(currentAddres++, 1); //data is in eeprom

    //message to eeprom
    for(int i = 0; i < messageLength; i++){
        eeprom_update_byte(currentAddres++, message[i]);
    }

    eeprom_update_byte(currentAddres++, brightness);

    //red values to eeprom
    for(int i = 0; i < messageLength; i+=2){
        if((i+1) < messageLength)
            eeprom_update_byte(currentAddres++, ((s_r[i] << 4) & 0xf0) | s_r[i+1]);
        else
            eeprom_update_byte(currentAddres++, ((s_r[i] << 4) & 0xf0) | s_g[0]);
    }

    //green values to eeprom
    for(int i = uneven; i < messageLength; i+=2){
        eeprom_update_byte(currentAddres++, ((s_g[i] << 4) & 0xf0) | s_g[i+1]);
    }

    //blue values to eeprom
    for(int i = 0; i < messageLength; i+=2){
        if((i+1) < messageLength)
            eeprom_update_byte(currentAddres++, ((s_b[i] << 4) & 0xf0) | s_b[i+1]);
        else
            eeprom_update_byte(currentAddres++, (s_b[i] << 4) & 0xf0);
    }

    //logo to eeprom
    for(int i = 0; i < AMOUNT; i++){
        for(int j = 0; j < AMOUNT; j+=2){
            eeprom_update_byte(currentAddres++, ((logo[i][j].red << 4) & 0xf0) | logo[i][j].blue);
            eeprom_update_byte(currentAddres++, ((logo[i][j].green << 4) & 0xf0) | logo[i][j+1].red);
            eeprom_update_byte(currentAddres++, ((logo[i][j+1].blue << 4) & 0xf0) | logo[i][j+1].green);
        }
    }
}

uint8_t readFromEeprom(char message[], uint8_t s_r[], uint8_t s_g[], uint8_t s_b[], Led logo[][AMOUNT], uint8_t *brightness){
    uint8_t currentAddres = 0;
    if(eeprom_read_byte(currentAddres++) != 1){
        return 0;
    }

    uint8_t messageLength = 0;
    while(1){
        message[messageLength] = eeprom_read_byte(currentAddres++);
        if(message[messageLength++] == '\0'){
            break;
        }
    }
    uint8_t uneven = messageLength%2;
    *brightness = eeprom_read_byte(currentAddres++);

    for(int i = 0; i < messageLength; i+=2){
        uint8_t data;
        data = eeprom_read_byte(currentAddres++);
        s_r[i] = (data >> 4) & 0x0f;

        if((i+1) < messageLength){
            s_r[i + 1] = data & 0x0f; 
        }else{
            s_g[0] = data & 0x0f;
        }
    }

    for(int i = uneven; i < messageLength; i+=2){
        uint8_t data;
        data = eeprom_read_byte(currentAddres++);
        s_g[i] = (data >> 4) & 0x0f;
        s_g[i + 1] = data & 0x0f; 
    }

    for(int i = 0; i < messageLength; i+=2){
        uint8_t data;
        data = eeprom_read_byte(currentAddres++);
        s_r[i] = (data >> 4) & 0x0f;

        if((i+1) < messageLength){
            s_r[i + 1] = data & 0x0f; 
        }
    }

    for(int i = 0; i < AMOUNT; i++){
        for(int j = 0; j < AMOUNT; j+=2){
            uint8_t data;
            data = eeprom_read_byte(currentAddres++);
            logo[i][j].red = (data >> 4) & 0x0f;
            logo[i][j].blue = data & 0x0f;

            data = eeprom_read_byte(currentAddres++);
            logo[i][j].green = (data >> 4) & 0x0f;
            logo[i][j+1].red = data & 0x0f;

            data = eeprom_read_byte(currentAddres++);
            logo[i][j+1].blue = (data >> 4) & 0x0f;
            logo[i][j+1].green = data & 0x0f;
        }
    }
    return 1;
}
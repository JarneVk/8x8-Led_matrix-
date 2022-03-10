
#include <avr/io.h>

//ontvanger
int sendSpecial(int dat);
void uarts_setup();

//zender
void timer_setup();
uint8_t getNextOutputData();
void SendNewColumn();

//Led's
void initLedPoorten();

void writeToLed(uint32_t bits[]);

//shiftTimer
void shiftTimer_setup();
void shiftTimer_reset();


uint8_t zender_buffer_uart1;
uint8_t ontvanger_buffer_uart0;
uint8_t zender_verbinding;
uint8_t zender_count_timeout;

uint8_t columnIndex;
uint8_t part;
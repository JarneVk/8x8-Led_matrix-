
#include <avr/io.h>

//ontvanger
/*void uartsetup_ontvanger_uart0();
int sendData_usart0(uint8_t hexgetal);
int sendSpecial_ontvanger(int dat);
void readuart0_interupt();

//zender
int sendData_zender_usart1(uint8_t hexgetal)
void timer_setup();
*/
uint8_t getNextOutputData();
/*
int sendSpecial_zender(int dat);
void SendNewColumn();
void interup_ReadData();

//Led's
void initLedPoorten();
void writeToLed(uint32_t bits[]);

//shiftTimer
void shiftTimer_setup();
void shiftTimer_reset();
*/

uint8_t zender_buffer_uart1;
uint8_t ontvanger_buffer_uart0;
uint8_t zender_verbinding;
uint8_t zender_count_timeout;

uint8_t columnIndex;
uint8_t part;
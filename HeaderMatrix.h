
#include <avr/io.h>

void uartsetup_zender_uart1();
void uartsetup_ontvanger_uart0();
//uint8_t getNextOutputData();
int sendSpecial();
void initLedPoorten();

uint8_t zender_buffer_uart1;
uint8_t ontvanger_buffer_uart0;
uint8_t zender_verbinding;
uint8_t zender_count_timeout;

uint8_t columnIndex;
uint8_t part;

#include <avr/io.h>

//aanzetten van printf_p (1164 bytes aan program data printf_p doet ook mallocs)
//ALLEEEN VOOR DEBUGGEEEN (stdio is +-1kb aan program memory)
//vb van gebruik printf_P(PSTR("dit mag alleen een literal string zijn %d"),i)
//  string in prog space^   ^ define voor string in program space te zetten
#define PRINTFP

//ontvanger
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


//computer communication
void USART3_Init();

/*
Define for easy string literal use
*/
#define printStringLiteral(ARG) PROG_printString(PSTR(ARG))
void PROG_printString(const char data[]);


uint8_t zender_buffer_uart1;
uint8_t ontvanger_buffer_uart0;
uint8_t zender_verbinding;
uint8_t zender_count_timeout;

uint8_t columnIndex;
uint8_t part;
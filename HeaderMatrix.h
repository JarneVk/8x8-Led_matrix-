
#include <avr/io.h>

//aanzetten van printf_p (1164 bytes aan program data printf_p doet ook mallocs)
//ALLEEEN VOOR DEBUGGEEEN (stdio is +-1kb aan program memory)
//vb van gebruik printf_P(PSTR("dit mag alleen een literal string zijn %d"),i)
//  string in prog space^   ^ define voor string in program space te zetten
#define PRINTFP
#ifdef PRINTFP
#include <stdio.h>
#endif

typedef struct led{
    uint8_t brightness; // amount of brightness : value between 0-31
    uint8_t red; //amount of red : value between 0-31
    uint8_t green; //amount of green : value between 0-31
    uint8_t blue; //amount of blue : value between 0-31
}Led;

#define MAX_STRING_LEN 30
#define MAX_MESSAGE_COLORS 5

#define AMOUNT 8
#define LETTER_WIDTH 4
#define MAX_STRING_LEN 30

//ontvanger
void uarts_setup();


//zender
void timer_setup();
uint8_t getNextOutputData();
//void SendColumn();

//Led's
void initLedPoorten();

void writeToLed(uint32_t bits[]);

//shiftTimer
void shiftTimer_reset();


//computer communication
void USART3_Init();
void USART3_sendChar(char data);

/*
Define for easy string literal use
*/
#define printStringLiteral(ARG) PROG_printString(PSTR(ARG))
void PROG_printString(const char data[]);
void SRAM_printBytes(uint8_t *data, uint8_t amount);


void masterShiftMatrixFullString();

void initGlobalVariables();

void driveLeds();

uint8_t string_red[MAX_STRING_LEN]; //the amount of red for each letter of the string
uint8_t string_green[MAX_STRING_LEN]; //the amount of green for each letter of the string
uint8_t string_blue[MAX_STRING_LEN]; //the amount of blue for each letter of the string
uint8_t string_brightness; //the brightness of the string to be displayed on the leds

uint8_t zender_buffer_uart1;
uint8_t ontvanger_buffer_uart0;
uint8_t zender_verbinding;
uint8_t zender_count_timeout;
uint8_t ontvangerNAck_count;
uint8_t stop_antwoorden;

uint8_t columnIndex;
uint8_t part;


int ontvang_i; //testing
void ledsAansturen();
//sent data
char inputString[MAX_STRING_LEN];
Led stringColor[MAX_MESSAGE_COLORS];
uint8_t colorIndex[MAX_MESSAGE_COLORS];


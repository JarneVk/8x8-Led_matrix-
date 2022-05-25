
#include <avr/io.h>

//aanzetten van printf_p (1164 bytes aan program data printf_p doet ook mallocs)
//ALLEEEN VOOR DEBUGGEEEN (stdio is +-1kb aan program memory)
//vb van gebruik printf_P(PSTR("dit mag alleen een literal string zijn %d"),i)
//  string in prog space^   ^ define voor string in program space te zetten
#define PRINTFP
#ifdef PRINTFP
#include <stdio.h>
#endif

#define AMOUNT 8
#define LETTER_WIDTH 4
#define MAX_STRING_LEN 35

typedef struct led{
    uint8_t brightness; // amount of brightness : value between 0-31
    uint8_t red; //amount of red : value between 0-31
    uint8_t green; //amount of green : value between 0-31
    uint8_t blue; //amount of blue : value between 0-31
}Led;


//ontvanger
void uarts_setup();

//zender
void timer_setup();
uint8_t getNextOutputData();
void sendNewColumn();

//Led's
void initLedPoorten();
void writeToLed(uint32_t bits[]);

//shiftTimer
void shiftTimer_reset();

int writeOntvangenData(uint8_t data);

//computer communication
void USART3_Init();
char inputString[MAX_STRING_LEN + 1];
uint8_t input_red[MAX_STRING_LEN]; //the amount of red for each letter of the string
uint8_t input_green[MAX_STRING_LEN]; //the amount of green for each letter of the string
uint8_t input_blue[MAX_STRING_LEN]; //the amount of blue for each letter of the string
uint8_t input_bgred[MAX_STRING_LEN]; //the amount of red for each letter of the string
uint8_t input_bggreen[MAX_STRING_LEN]; //the amount of green for each letter of the string
uint8_t input_bgblue[MAX_STRING_LEN]; //the amount of blue for each letter of the string
uint8_t input_brightness; //the brightness of the string to be displayed on the leds

//andere belangrijke dingen
void masterShiftMatrixFullString();
void initGlobalVariables();
void driveLeds();
void getUserInput(char inputString[], uint8_t s_r[], uint8_t s_b[], uint8_t s_g[] ,uint8_t brightness);
void getUserLogo(Led inputLogo[][AMOUNT]);


uint8_t zender_buffer_uart1;
uint8_t ontvanger_buffer_uart0;
volatile uint8_t zender_count_timeout;
volatile uint8_t NAck_count;

volatile uint8_t columnIndex;
volatile uint8_t part;


int ontvang_i; //testing
void ledsAansturen();
void zender_timer_setup();

//eeprom
void writeToEeprom(char message[], uint8_t s_r[], uint8_t s_g[], uint8_t s_b[], Led logo[][AMOUNT], uint8_t brightness);
uint8_t readFromEeprom(char message[], uint8_t s_r[], uint8_t s_g[], uint8_t s_b[], Led logo[][AMOUNT], uint8_t *brightness);


void endOntvanger();


volatile uint8_t ontvangerEnd;
volatile uint8_t zenderEnd;

//differentatie tussen master en slave
uint8_t master;

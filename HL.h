#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <avr/pgmspace.h>
#include "HeaderMatrix.h"

// #define AMOUNT 8
// #define LETTER_WIDTH 4
// #define MAX_STRING_LEN 30

//structure to represent a single led in led matrix
// typedef struct led{
//     uint8_t brightness; // amount of brightness : value between 0-31
//     uint8_t red; //amount of red : value between 0-31
//     uint8_t green; //amount of green : value between 0-31
//     uint8_t blue; //amount of blue : value between 0-31
// }Led;

//function prototypes:
//**********INIT MODULE**********
//void initGlobalVariables();

//**********I/O MODULE**********
uint16_t ledToOutput(Led pixel);
uint32_t ledToHardwareDriver(Led pixel);
void decompressReceivedPackages(Led columnReceived[], uint8_t array_ont[]);
void inputToLed(Led pixel, uint8_t input1, uint8_t input2);
void getUserInput();

//**********DATA PROCESSING**********
void enterLetterInMatrix(Led m[][LETTER_WIDTH],const uint8_t letterMatrix[][LETTER_WIDTH], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void shiftMatrix(Led columnReceived[AMOUNT]);
void masterShiftMatrix(Led letter[][LETTER_WIDTH]);
//void masterShiftMatrixFullString();
void charToLedLetter(char cha, Led letter[][LETTER_WIDTH], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);

//**********TESTING FUNCTIONS**********
void fillLedMatrixWithValue(Led m[][AMOUNT], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void printLedMatrixToTerminal(Led m[][AMOUNT]);
void printMatrixToTerminal(uint8_t matrix[][LETTER_WIDTH]);
void initLedMatrix1d(Led matrix[AMOUNT], uint8_t value);
void sendColumn();
void sendNewColumn();

//*****global variables*****:

//for the function getNextOutputData:
//uint8_t columnIndex; 
//uint8_t part;
Led columnSend[AMOUNT]; //for the function shiftMatrix and getNextOuputData
                        //the column to be send to the next board

//for the function masterShiftMatrix
uint8_t columnLetterToShiftIn; //the column of the letter to be shifted in 0-3

//for the function masterShiftMatrixFullString
uint8_t letterNr; //the counter of the letter in the string

//general use global variables
char string[MAX_STRING_LEN]="Something"; //the string to be displayed on screen
// uint8_t string_red[MAX_STRING_LEN]; //the amount of red for each letter of the string
// uint8_t string_green[MAX_STRING_LEN]; //the amount of green for each letter of the string
// uint8_t string_blue[MAX_STRING_LEN]; //the amount of blue for each letter of the string
// uint8_t string_brightness=10; //the brightness of the string to be displayed on the leds
Led main_matrix[AMOUNT][AMOUNT]; //the matrix of this LED BOARD

const uint8_t matrix_a[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_b[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_c[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,0,1,1},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,0,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_d[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_e[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,1},
                                                       {0,1,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_f[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,1},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,0,0,0}};
const uint8_t matrix_g[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,0,1,1},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_h[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_i[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,1},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,1,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_j[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,0,0,1},
                                                       {0,0,0,1},
                                                       {0,0,0,1},
                                                       {0,0,0,1},
                                                       {0,1,0,1},
                                                       {0,0,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_k[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_l[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,1,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_m[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,1,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_n[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_o[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,0,1,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_p[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,1,0,0},
                                                       {0,1,0,0},
                                                       {0,0,0,0}};
const uint8_t matrix_q[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,1},
                                                       {0,0,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_r[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_s[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,0,1,1},
                                                       {0,1,0,0},
                                                       {0,0,1,0},
                                                       {0,0,0,1},
                                                       {0,0,0,1},
                                                       {0,1,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_t[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,1},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_u[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_v[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_w[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,1,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_x[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,0,0}};
const uint8_t matrix_y[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,1,0,1},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,0,0,0}};
const uint8_t matrix_z[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                       {0,1,1,1},
                                                       {0,0,0,1},
                                                       {0,0,1,0},
                                                       {0,0,1,0},
                                                       {0,1,0,0},
                                                       {0,1,1,1},
                                                       {0,0,0,0}};
const uint8_t matrix_space[AMOUNT][LETTER_WIDTH] PROGMEM = {{0,0,0,0},
                                                           {0,0,0,0},
                                                           {0,0,0,0},
                                                           {0,0,0,0},
                                                           {0,0,0,0},
                                                           {0,0,0,0},
                                                           {0,0,0,0},
                                                           {0,0,0,0}};

#include <stdio.h>
#include <stdlib.h>

#define AMOUNT 8
#define LETTER_WIDTH 4
#define MAX_STRING_LEN 50
//structure to represent a single led in led matrix
typedef struct led{
    uint8_t brightness; // amount of brightness : value between 0-31
    uint8_t red; //amount of red : value between 0-31
    uint8_t green; //amount of green : value between 0-31
    uint8_t blue; //amount of blue : value between 0-31
}Led;

//function prototypes:
void fillLedMatrixWithValue(Led m[][AMOUNT], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void enterLetterInMatrix(Led m[][LETTER_WIDTH], uint8_t letterMatrix[][LETTER_WIDTH], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void printLedMatrixToTerminal(Led m[][AMOUNT]);
void printMatrixToTerminal(uint8_t matrix[][LETTER_WIDTH]);
void shiftMatrix(Led matrix[][AMOUNT], Led columnReceived[AMOUNT]);
void masterShiftMatrix(Led matrix[][AMOUNT],Led letter[][LETTER_WIDTH]);
void initLedMatrix1d(Led matrix[AMOUNT], uint8_t value);
void charToLedLetter(char cha, Led letter[][LETTER_WIDTH], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void masterShiftMatrixFullString(Led matrix[][AMOUNT], uint8_t brightness, uint8_t red[MAX_STRING_LEN], uint8_t green[MAX_STRING_LEN], uint8_t blue[MAX_STRING_LEN]);
uint16_t ledToOutput(Led pixel);
void inputToLed(Led pixel, uint8_t input1, uint8_t input2);
uint8_t getNextOuputData();
uint32_t ledToHardwareDriver(Led pixel);
void sendColumn();
void getUserInput();


//global variables:

uint8_t columnIndex; //for the function getNextOuputData
uint8_t part; //for the function getNextOuputData
Led columnSend[AMOUNT]; //for the function shiftMatrix and getNextOuputData
char string[MAX_STRING_LEN]="Something"; //the string to be displayed on screen

uint8_t matrix_a[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_b[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,0,0,0}};
uint8_t matrix_c[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,0,1,1},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,0,1,1},
                                       {0,0,0,0}};
uint8_t matrix_d[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,0,0,0}};
uint8_t matrix_e[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,1},
                                       {0,1,0,0},
                                       {0,1,1,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,1,1},
                                       {0,0,0,0}};
uint8_t matrix_f[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,1},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,1,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,0,0,0}};
uint8_t matrix_g[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,0,1,1},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,1,1},
                                       {0,0,0,0}};
uint8_t matrix_h[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_i[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,1},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,1,1,1},
                                       {0,0,0,0}};
uint8_t matrix_j[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,0,0,1},
                                       {0,0,0,1},
                                       {0,0,0,1},
                                       {0,0,0,1},
                                       {0,1,0,1},
                                       {0,0,1,1},
                                       {0,0,0,0}};
uint8_t matrix_k[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_l[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,1,1,1},
                                       {0,0,0,0}};
uint8_t matrix_m[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,1,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_n[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_o[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,0,1,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,0,0,0}};
uint8_t matrix_p[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,1,0,0},
                                       {0,1,0,0},
                                       {0,0,0,0}};
uint8_t matrix_q[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,1},
                                       {0,0,1,1},
                                       {0,0,0,0}};
uint8_t matrix_r[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_s[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,0,1,1},
                                       {0,1,0,0},
                                       {0,0,1,0},
                                       {0,0,0,1},
                                       {0,0,0,1},
                                       {0,1,1,0},
                                       {0,0,0,0}};
uint8_t matrix_t[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,1},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,0,0}};
uint8_t matrix_u[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,0},
                                       {0,0,0,0}};
uint8_t matrix_v[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,0,0}};
uint8_t matrix_w[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,1,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_x[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,0,0}};
uint8_t matrix_y[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,1,0,1},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,0,0,0}};
uint8_t matrix_z[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                       {0,1,1,1},
                                       {0,0,0,1},
                                       {0,0,1,0},
                                       {0,0,1,0},
                                       {0,1,0,0},
                                       {0,1,1,1},
                                       {0,0,0,0}};
uint8_t matrix_space[AMOUNT][LETTER_WIDTH]= {{0,0,0,0},
                                           {0,0,0,0},
                                           {0,0,0,0},
                                           {0,0,0,0},
                                           {0,0,0,0},
                                           {0,0,0,0},
                                           {0,0,0,0},
                                           {0,0,0,0}};

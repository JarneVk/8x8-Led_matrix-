#include "main.h"

//function to fill in a led matrix with a single brightness value for testing purposes...
//@param m: The led matrix to be filled with brightness values.
//@param brightness: The brightness value each led is set to.
//@param red: the amount of red for the led
//@param blue: the amount of blue for the led
//@param green: the amount of green for the led
void fillLedMatrixWithValue(Led m[][AMOUNT], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    for(int row=0; row<AMOUNT; row++) {
        for(int col=0; col<AMOUNT; col++) {
            m[row][col].brightness=brightness;
            m[row][col].red=red;
            m[row][col].green=green;
            m[row][col].blue=blue;
        }
    }
}

//function to enter a letter into a led matrix that is ready to be loaded into the master
//@param m: The led matrix which represents a letter in an 8x4 led matrix
//@param letterMatrix: The matrix that determines which led's are turned on to represent a certain letter on the led panel.
//@param brightness: The brightness value each led that is turned on is set to.
//@param red: the amount of red for the led
//@param blue: the amount of blue for the led
//@param green: the amount of green for the led
void enterLetterInMatrix(Led m[][LETTER_WIDTH], uint8_t letterMatrix[][LETTER_WIDTH], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    for(int row=0; row<AMOUNT; row++) {
        for(int col=0; col<LETTER_WIDTH; col++) {
            if( letterMatrix[row][col] != 0) { //letterMatrix determines which leds are turned on with the specified brightness
                m[row][col].brightness=brightness;
            }
            else {
                m[row][col].brightness=0;
            }
            m[row][col].red= red;
            m[row][col].blue= blue;
            m[row][col].green= green;

        }
    }
}

//function to print the brightness levels of each led in a matrix panel to the terminal
//@param m: The led matrix to be printed to the terminal.
void printLedMatrixToTerminal(Led m[][AMOUNT]) {
    for(int row=0; row<AMOUNT; row++) {
        for(int col=0; col<AMOUNT; col++) {
            printf("%5d",m[row][col].brightness);
        }
        printf("\n");
    }
    printf("\n");
}

//function to print an 8x4 matrix to the terminal for testing purposes
//@param matrix: the 8x4 matrix to be printed.
void printMatrixToTerminal(uint8_t matrix[][LETTER_WIDTH]){
    for(int i=0; i<AMOUNT; i++) {
        for(int j=0; j<LETTER_WIDTH; j++) {
            printf("%5d",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Function to shift the matrix columns one position to the left
//@param matrix: the matrix to be shifted
//@param columnReveived: the column received from the previous board
//@param columnSend: the column to be sent to the next board -->global variable
void shiftMatrix(Led matrix[][AMOUNT], Led columnReceived[AMOUNT]) {

    for(int j=0; j<AMOUNT; j++) {
        if(j==0) {
            for(int i=0; i<AMOUNT; i++) {
                columnSend[i]=matrix[i][j]; //copying the first column to send to the next matrix
            }
        }
        if(j<AMOUNT-1){
            for(int i=0; i<AMOUNT; i++) {
                matrix[i][j]=matrix[i][j+1];//shiting columns to the left
            }
        }
        else{ //if(j==AMOUNT-1){
            for(int i=0; i<AMOUNT; i++) {
                matrix[i][j]=columnReceived[i];//loading in the last column
            }
        }
    }
}

//function to gradually shift in a letter to the master's matrix.
//@param matrix: the led matrix from the master
//@param letter: a led matrix that contains the letter to be shifted in
//@param columnSend: the column to be sent to the next board -->global variable
void masterShiftMatrix(Led matrix[][AMOUNT],Led letter[][LETTER_WIDTH]) {
    Led cr[AMOUNT];//column received
    for(int j=0;j<LETTER_WIDTH; j++) {
        for(int i=0;i<AMOUNT; i++) {
            cr[i] = letter[i][j]; //copying a column of the letter to be shifted in
        }
        shiftMatrix(matrix,cr);
        printLedMatrixToTerminal(matrix); //testing print
        //printf("\n");// testing print
    }

}

//function to make a 1d matrix of Leds filled with a certain brightness value for testing purposes
//@param matrix: the matrix to be initialized
//@param value: the brightness value to initialize
void initLedMatrix1d(Led matrix[AMOUNT], uint8_t value){
    for(int i=0; i<AMOUNT; i++) {
        matrix[i].brightness = value;
        matrix[i].red = 0;
        matrix[i].blue = 0;
        matrix[i].green = 0;
    }
}

//function to convert a given character to a corresponding led matrix
//@param cha: the character that needs to be converted to a led matrix
//@param letter: the place the resulting led matrix should be stored
//@param brightness: the brightness of the letter
//@param red: the amount of red
//@param green: the amount of red
//@param blue: the amount of red
void charToLedLetter(char cha, Led letter[][LETTER_WIDTH], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue){
    switch (cha)
    {
        case 'a': enterLetterInMatrix(letter,matrix_a, brightness, red, green, blue);      break;
        case 'b': enterLetterInMatrix(letter,matrix_b, brightness, red, green, blue);      break;
        case 'c': enterLetterInMatrix(letter,matrix_c, brightness, red, green, blue);      break;
        case 'd': enterLetterInMatrix(letter,matrix_d, brightness, red, green, blue);      break;
        case 'e': enterLetterInMatrix(letter,matrix_e, brightness, red, green, blue);      break;
        case 'f': enterLetterInMatrix(letter,matrix_f, brightness, red, green, blue);      break;
        case 'g': enterLetterInMatrix(letter,matrix_g, brightness, red, green, blue);      break;
        case 'h': enterLetterInMatrix(letter,matrix_h, brightness, red, green, blue);      break;
        case 'i': enterLetterInMatrix(letter,matrix_i, brightness, red, green, blue);      break;
        case 'j': enterLetterInMatrix(letter,matrix_j, brightness, red, green, blue);      break;
        case 'k': enterLetterInMatrix(letter,matrix_k, brightness, red, green, blue);      break;
        case 'l': enterLetterInMatrix(letter,matrix_l, brightness, red, green, blue);      break;
        case 'm': enterLetterInMatrix(letter,matrix_m, brightness, red, green, blue);      break;
        case 'n': enterLetterInMatrix(letter,matrix_n, brightness, red, green, blue);      break;
        case 'o': enterLetterInMatrix(letter,matrix_o, brightness, red, green, blue);      break;
        case 'p': enterLetterInMatrix(letter,matrix_p, brightness, red, green, blue);      break;
        case 'q': enterLetterInMatrix(letter,matrix_q, brightness, red, green, blue);      break;
        case 'r': enterLetterInMatrix(letter,matrix_r, brightness, red, green, blue);      break;
        case 's': enterLetterInMatrix(letter,matrix_s, brightness, red, green, blue);      break;
        case 't': enterLetterInMatrix(letter,matrix_t, brightness, red, green, blue);      break;
        case 'u': enterLetterInMatrix(letter,matrix_u, brightness, red, green, blue);      break;
        case 'v': enterLetterInMatrix(letter,matrix_v, brightness, red, green, blue);      break;
        case 'w': enterLetterInMatrix(letter,matrix_w, brightness, red, green, blue);      break;
        case 'x': enterLetterInMatrix(letter,matrix_x, brightness, red, green, blue);      break;
        case 'y': enterLetterInMatrix(letter,matrix_y, brightness, red, green, blue);      break;
        case 'z': enterLetterInMatrix(letter,matrix_z, brightness, red, green, blue);      break;

        case ' ': enterLetterInMatrix(letter,matrix_space, brightness, red, green, blue);  break;

        default:  printf("Error: Undefined Character\n");
    }
}

//function to gradually shift in a string to the master's matrix. Each letter can be a different color.
//@param matrix: the led matrix from the master
//@param string: a string of letters to be shifted in
//@param columnSend: the column to be sent to the next board
//@param brightness: the brightness of the text
//@param red: matrix with the amount of red for every letter
//@param green: matrix with the amount of green for every letter
//@param blue: matrix with the amount of blue for every letter
void masterShiftMatrixFullString(Led matrix[][AMOUNT], uint8_t brightness, uint8_t red[MAX_STRING_LEN], uint8_t green[MAX_STRING_LEN], uint8_t blue[MAX_STRING_LEN]) {
    Led letter[AMOUNT][LETTER_WIDTH];
    int count=0;
    while (count<MAX_STRING_LEN && string[count]!='\0'){
        //printf("next letter=%c\n",string[count]);
        charToLedLetter(string[count],letter, brightness, red[count], green[count], blue[count]);
        masterShiftMatrix(matrix,letter);
        count++;
    }
}

//function to convert a led pixel to a compressed format to send between PCB's
//format: 16bit -> BBBBBBBBGGGGRRRR 
// 4 bit brightness, 4 bit blue, 4bit green, 4bit red
//@param pixel: the led that needs to be converted
//@return: the output-code needed to activate the led correctly
uint16_t ledToOutput(Led pixel) {
    uint16_t brightness_send, blue_send, green_send, red_send;
    uint16_t output =0;
    brightness_send= (uint16_t)pixel.brightness<<12; //take the 4 LSB's from brightness and put in bit 15 until 12 of brightness_send
    brightness_send &= 0b1111000000000000; //mask for bit 15 until 12
    blue_send = (uint16_t)pixel.blue<<8; //take the 4 LSB's from brightness and put in bit 11 until 8 of blue_send
    blue_send &= 0b0000111100000000; //mask for bit 11 until 8
    green_send = (uint16_t)pixel.green<<4; //take the 4 LSB's from brightness and put in bit 7 until 4 of green_send
    green_send &= 0b0000000011110000; //mask for bit 7 until 4
    red_send = (uint16_t)pixel.red; //take the 4 LSB's from brightness and put in bit 3 until 0 of red_send
    red_send&= 0b0000000000001111; //mask for bit 3 until 0
    output = brightness_send + blue_send + green_send + red_send; //concatenate the 4 pieces of information in a 2 byte unsigned int
    return output;
}

//function that converts the received input bytes (input1 and input2) in compressed format to Led structure format
//this is the inverse operation of ledToOuput (decrompession)
//@param Pixel: an element of the column received to be initialized with the values received from the compressed format
//@param input1: the first byte received associated with this pixel
//@param input2: the second byte received associated with this pixel
void inputToLed(Led pixel, uint8_t input1, uint8_t input2) {
    pixel.brightness = (input1>>4) & 0b00001111;
    pixel.blue = input1 & 0b00001111;
    pixel.green = (input2>>4) & 0b00001111;
    pixel.red = input2 & 0b00001111;
}

//converts the next element of the column to be sent to the next slave into the compressed format for sending 
//@param columnSend: the column to be send to the next slave in Led structure format, you have to call the function
//twice with this index so that both part1 and part2 can be transmitted. -->global variable
//@param columnIndex: the index of the element of the column you are trying to send -->global variable
//@return: the next element to be send to the slave (in 16 bit compressed format BBBBBBBBGGGGRRRR)
uint8_t getNextOuputData() {
    uint16_t nextElement;
    if(columnIndex > 7) {
        return 0; // columnIndex out of bounce
    }
    nextElement = ledToOutput(columnSend[columnIndex]);
    if(part == 0) {
        part=1;
        return (uint8_t)nextElement>>8;//return first 8 bit 
    }
    else { //part==1
        part=0;
        columnIndex++; 
        return (uint8_t)nextElement; //return last 8 bit 
    }
}

//converts a Led datastructure to hardware format to send to led's (data frame to send to the leds)
//data frame format: triple 1 + 5bit brightness, 8bit blue, 8bit green, 8bit red : format 111BBBBB BBBBBBBB GGGGGGGG RRRRRRRR
//because all our values are sent in 4bit the practical format will be: 111BBBB0 BBBB0000 GGGG0000 RRRR0000
//@param pixel: an element of the led matrix to convert into hardware 
//@return: returns a 32bit value to drive hardware of 1 led
uint32_t ledToHardwareDriver(Led pixel) {
    uint32_t brightness_driver, blue_driver, green_driver, red_driver;
    uint32_t hardwareDriver=0;
    brightness_driver= ((uint32_t)pixel.brightness<<25 ) | 0b11100000000000000000000000000000; //format 111BBBB0 00000000 00000000 00000000
    blue_driver = (uint32_t)pixel.blue<<20;   //format 00000000 BBBB0000 00000000 00000000
    green_driver = (uint32_t)pixel.green<<12; //format 00000000 00000000 GGGG0000 00000000
    red_driver = (uint32_t)pixel.red<<4;      //format 00000000 00000000 00000000 RRRR0000
    hardwareDriver = brightness_driver + blue_driver + green_driver + red_driver;//format 111BBBB0 BBBB0000 GGGG0000 RRRR0000
    return hardwareDriver;
}

void sendColumn() {
    //sendNewColumn (function from jakke)
}

//method to get the input string from the user
void getUserInput() {
    char userInput[MAX_STRING_LEN]="Test str";
    for(int i=0; i<MAX_STRING_LEN; i++ ){
        if(userInput[i] == '\0') {
            break;
        }
        string[i]=userInput[i];
    }
}

/*
    main for master
    initHardware()
    getUserInput()
    masterShiftMatrixFullString(m, bright, red[], green[], blue[]) <---- potentially with gui
    sendColumn()
    driveLeds()
*/

/*
    main for slave
    Led columnReceived[AMOUNT];
    initHardware()
    receiveData() -> fill in column received with inputToLed, return 1 -> expect something, return 0 -> expect nothing :)
    shiftmatrix(m, columnReceived)
    sendColumn()
    driveLeds()

*/

int main(int argc, char *argv[]) {

    Led matrix0[AMOUNT][AMOUNT];

    fillLedMatrixWithValue(matrix0, 31, 31, 0, 0);
    printf("Testing a matrix filled with 31 everywhere: \n");
    printLedMatrixToTerminal(matrix0);

    printf("Testing letter matrix 'a': \n");
    printMatrixToTerminal(matrix_a); //test to see if global variables are available here

    //testing master matrix shift
    Led matrix1[AMOUNT][AMOUNT];
    Led letter[AMOUNT][LETTER_WIDTH];
    enterLetterInMatrix(letter,matrix_y,31, 31, 0, 0);
    fillLedMatrixWithValue(matrix1,0, 31, 0, 0);
    //Led cs1[AMOUNT];
    printf("Testing masterShiftMatrix:\n\n");
    masterShiftMatrix(matrix1,letter);

    //testing master matrix shifting a full string
    getUserInput();
    Led matrix3[AMOUNT][AMOUNT];
    uint8_t red[MAX_STRING_LEN]={31,31,31,31,31,31,31,31};
    uint8_t green[MAX_STRING_LEN]={0,0,0,0,0,0,0,0};
    uint8_t blue[MAX_STRING_LEN]={0,0,0,0,0,0,0,0};
    fillLedMatrixWithValue(matrix3,0, 31, 0, 0);
    printf("Testing masterShiftMatrixFullString:\n\n");
    masterShiftMatrixFullString(matrix3,31,red,green,blue);


    //testing the matrix shift by shifting the letter b that was just loaded into the master matrix:
    /*
        printf("Testing shiftMatrix:\n");
        Led cr[AMOUNT];
        //initLedMatrix1d(cr,15);
        printLedMatrixToTerminal(matrix1);
        for(int i=0; i<AMOUNT; i++) {
            printf("The matrix after shift %d\n",i);
            shiftMatrix(matrix1,cr); 
            printLedMatrixToTerminal(matrix1);
            printf("The column send:\n");
            for(int i=0; i<AMOUNT; i++) {
                printf("%5d",(cs[i]).brightness);
            }
            printf("\n\n");
        }
    */
}

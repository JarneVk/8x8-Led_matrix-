//HL.c file made by Olivier & Jorn
//HL= high level code
#include "HL.h"



//**********INIT MODULE**********

//function to initialise all global variables used for the led board
void initGlobalVariables() {
    fillLedMatrixWithValue(main_matrix,0,0,0,0);//filling the entire matrix with 0's
    for (int i = 0; i < MAX_STRING_LEN; i++) {
        string_blue[i]=0;
        string_red[i]=0;
        string_blue[i]=0;
    }    
}

//**********I/O MODULE**********

//FUNCTIONS FOR OUPUT:

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
    //// printf_P(PSTR("output : %d \n\r"),output);
    return output;
}

//converts the next element of the column to be sent to the next slave into the compressed format for sending 
//@param columnSend: the column to be send to the next slave in Led structure format, you have to call the function
//twice with this index so that both part1 and part2 can be transmitted. -->global variable
//@param columnIndex: the index of the element of the column you are trying to send -->global variable
//@return: the next element to be send to the slave (in 16 bit compressed format BBBBBBBBGGGGRRRR)
uint8_t getNextOutputData() {
    uint16_t nextElement;
    //// printf_P(PSTR("column index :%d \n\r"),columnIndex);
    if(columnIndex > 7) {
        return 0; // columnIndex out of bounce
    }
    nextElement = ledToOutput(columnSend[columnIndex]);
    if(part == 0) {
        part=1;
        return (uint8_t)(nextElement>>8);//return first 8 bit 
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

//function to drive the led hardware with the main_matrix
//we run through the matrix from the right bottem corner then up left down left up etc...
//Global vars used here:
//*main_matrix
void driveLeds(){
    //printf_P(PSTR("dl \n\r"));
    uint32_t ledArray[AMOUNT*AMOUNT];
    for(int col=AMOUNT-1; col>=0; col--) {
        for(int row=AMOUNT-1; row>=0; row--) {
            int row2;
            if(col%2==0) {
                row2=AMOUNT-1-row; //uneven rows in reverse order
            }
            else{
                row2=row;
            }
            uint32_t hwDriver = ledToHardwareDriver(main_matrix[row2][col]);
            int row_led=AMOUNT-1-row;
            int col_led=AMOUNT-1-col;
            ledArray[col_led*AMOUNT+row_led] = hwDriver;
        }
    }
    /*
    //printf_P(PSTR("leds\n\r"));
    for(int col=AMOUNT-1; col>=0; col--) {
        for(int row=AMOUNT-1; row>=0; row--) {
            if(col%2) {
                row=AMOUNT-1-row; //uneven rows in reverse order
            }
            if(ledArray[row+col*AMOUNT]&(uint32_t)0b00000000000000000000000011111111)
                //printf_P(PSTR("1   "));
            else
                //printf_P(PSTR("0   "));
        }
        //printf_P(PSTR("\n\r"));
    }*/
    writeToLed(ledArray);
}

//FUNCTIONS FOR INPUT:

static uint8_t array_ont[16];
int writeOntvangenData(uint8_t data){
    if(ontvang_i>14){
        return 1;
    } else  {
        array_ont[ontvang_i] = data;
        ontvang_i ++;
        return 0;
    }
}

void endOntvanger(){
    // for(int i=0; i<16;i++){
        //// printf_P(PSTR("%d"),array_ont[i]);
    // }
    //// printf_P(PSTR("\n\r"));
    Led columnReceived[AMOUNT]; 
    decompressReceivedPackages(columnReceived,array_ont);
    // for(int i=0;i<AMOUNT;i++){
        //// printf_P(PSTR("%d"),columnReceived[i].brightness);
    // }
    
    shiftMatrix(columnReceived);
}


//function to decompress 16 received packages (in array_ont) and put the result in a columnReceived array
//that is ready to be shifted in to the main_matrix of the slave with shiftMatrix(columnReceived);
//@param columnReceived: a Led array that will be filled in by this function
//@param array_ont: the array that contains the 16 received packages
void decompressReceivedPackages(Led columnReceived[], uint8_t array_ont[]) {
    for(int i=0;i<AMOUNT;i++) {
        Led pixel;
        pixel = inputToLed(array_ont[2*i],array_ont[2*i+1]); //<— invullen column received
        columnReceived[i] = pixel;
    }
}

//function that converts the received input bytes (input1 and input2) in compressed format to Led structure format
//this is the inverse operation of ledToOuput (decrompession)
//@param Pixel: an element of the column received to be initialized with the values received from the compressed format
//@param input1: the first byte received associated with this pixel
//@param input2: the second byte received associated with this pixel
Led inputToLed(uint8_t input1, uint8_t input2) {
    Led pixel;
    pixel.brightness = (input1>>4);
    pixel.brightness &= 0b00001111;
    pixel.blue = input1 & 0b00001111;
    ////printf_P(PSTR("blue : %d"),pixel.blue);
    pixel.green = (input2>>4) ;
    pixel.green &= 0b00001111;
    ////printf_P(PSTR("green : %d"),pixel.green);
    pixel.red = input2 & 0b00001111;
    ////printf_P(PSTR("red : %d \n\r"),pixel.red);
    return pixel;
}

//const char wou hem ook niet raar genoeg
char userInput[MAX_STRING_LEN]="Test str";
//method to get the input string from the user
void getUserInput() {
    //string niet declareren lokaal?
    /*for(int i=0; i<MAX_STRING_LEN; i++ ){
        //printf_P(PSTR("%c,%x"),userInput[i],userInput[i]);
    }*/
    //// printf_P(PSTR("\n\r\n\r"));
    int i;
    for(i=0; i<MAX_STRING_LEN; i++ ){
        if(userInput[i] == '\0') {
            break; //end of user input
        }
        string[i]=userInput[i];
        //// printf_P(PSTR("nieuwe c %d:%c  %x\n\r"),i,string[i],string[i]);
        string_red[i]=15;
        string_blue[i]=12;
        string_green[i]=7;
    }
    while(i<MAX_STRING_LEN) {
        string[i]='\0'; //for the remaining lenght of the string , fill up with 0 chars
        i++;
    } 
    //// printf_P(PSTR("nieuwe string:%s\n\r"),string);
    string_brightness=20;
}

//**********DATA PROCESSING**********

//function to enter a letter into a led matrix that is ready to be loaded into the master
//@param m: The led matrix which represents a letter in an 8x4 led matrix
//@param letterMatrix: The matrix that determines which led's are turned on to represent a certain letter on the led panel.
//@param brightness: The brightness value each led that is turned on is set to.
//@param red: the amount of red for the led
//@param blue: the amount of blue for the led
//@param green: the amount of green for the led
void enterLetterInMatrix(Led m[][LETTER_WIDTH], const uint8_t letterMatrix[][LETTER_WIDTH], uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    for(int row=0; row<AMOUNT; row++) {
        for(int col=0; col<LETTER_WIDTH; col++) {
            if( pgm_read_byte(&letterMatrix[row][col]) != 0) { //letterMatrix determines which leds are turned on with the specified brightness
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

//Function to shift the matrix columns one position to the left
//Global vars used here:
//*main_matrix: the matrix of the led board to be shifted
//*columnSend: the column to be send to the next board
//@param columnReveived: the column received from the previous board
void shiftMatrix(Led columnReceived[AMOUNT]) {

    for(int j=0; j<AMOUNT; j++) {
        if(j==0) {
            for(int i=0; i<AMOUNT; i++) {
                columnSend[i]=main_matrix[i][j]; //copying the first column to send to the next matrix
            }
        }
        if(j<AMOUNT-1){
            for(int i=0; i<AMOUNT; i++) {
                main_matrix[i][j]=main_matrix[i][j+1];//shiting columns to the left
            }
        }
        else{ //if(j==AMOUNT-1){
            for(int i=0; i<AMOUNT; i++) {
                main_matrix[i][j]=columnReceived[i];//loading in the last column
            }
        }
    }
}

//function to gradually shift in a letter to the master's matrix.
//Global vars used here:
//*columnLetterToShiftIn: the column of the letter to be shifted in (0-3), for 1 letter this function is called 4 times.      
//@param letter: a led matrix that contains the letter to be shifted in
void masterShiftMatrix(Led letter[][LETTER_WIDTH]) {
    Led cr[AMOUNT];//column received

   /* if( columnLetterToShiftIn > 3 ) {
        //printf_P(PSTR("columnLetter out of bounds! Trouble in masterShiftMatrix\n\r"));
    }*/
    for(int i=0;i<AMOUNT; i++) {
        cr[i] = letter[i][columnLetterToShiftIn]; //copying a column of the letter to be shifted in
    }
    shiftMatrix(cr);
    //printLedMatrixToTerminal(main_matrix); //testing print
    if(columnLetterToShiftIn ==3) {
        columnLetterToShiftIn=0;//this letter is shifted in, next letter will be shifted in on the next call
    }
    else {
        columnLetterToShiftIn++;//increment the column index for the next time this function is called
    }
}

//function to gradually shift in a string to the master's matrix. Each letter can be a different color.
//Global vars used here:
//*string: a string of letters to be shifted in 
//*columnSend: the column to be sent to the next board 
//*string_red: matrix with the amount of red for every letter 
//*string_green: matrix with the amount of green for every letter
//*string_blue: matrix with the amount of blue for every letter
//*string_brightness: the brightness of the text
//*columnLetterToShiftIn: to check if the letter is fully shifted...
void masterShiftMatrixFullString() {
    Led letter[AMOUNT][LETTER_WIDTH];
    
    if (letterNr<MAX_STRING_LEN && string[letterNr]!='\0'){
        //// printf_P(PSTR("string[letterNr] %d : %c\n\r"),letterNr,string[letterNr]);
        charToLedLetter(string[letterNr],letter, string_brightness, string_red[letterNr], string_green[letterNr], string_blue[letterNr]);
        masterShiftMatrix(letter);
        if(columnLetterToShiftIn ==0) {
            letterNr++; //the previous letter is shifted in when columnLetter is back at 0, so go to next letter
        }
    }
    else {
        charToLedLetter(' ',letter, 0, 0, 0, 0);
        masterShiftMatrix(letter);
        if(columnLetterToShiftIn == 0) { //space is fully shifted in
            letterNr=0; //start again from beginning of the string
        }
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
    //// printf_P(PSTR("karakter: %c\n\r"),cha);
    cha = tolower(cha); //only lowercase letters
    //// printf_P(PSTR("karakter: %c\n\r"),cha);
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

        //default:  printf_P(PSTR("Error: Undefined Character\n\r"));
    }
}

//**********TESTING FUNCTIONS**********


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

//function to print the brightness levels of each led in a matrix panel to the terminal (8x8 led matrix)
//@param m: The led matrix to be printed to the terminal.
void printLedMatrixToTerminal(Led m[][AMOUNT]) {
    for(int row=0; row<AMOUNT; row++) {
        for(int col=0; col<AMOUNT; col++) {
            //printf_P(PSTR("%5d    "),m[row][col].brightness);
        }
        //printf_P(PSTR("\n\r"));
    }
    //printf_P(PSTR("\n\r"));
}

//function to print an 8x4 matrix to the terminal for testing purposes
//@param matrix: the 8x4 matrix to be printed.
void printMatrixToTerminal_P(const uint8_t matrix[][LETTER_WIDTH]){
    for(int i=0; i<AMOUNT; i++) {
        for(int j=0; j<LETTER_WIDTH; j++) {
            //printf_P(PSTR("%5d    "),pgm_read_byte(&matrix[i][j]));
        }
        //printf_P(PSTR("\n\r"));
    }
    //printf_P(PSTR("\n\r"));
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

void sendColumn() {
    sendNewColumn(); //function in uartZender
}

/*
    main for master
    initGlobalVariables()
    initHardware()
    getUserInput()
    masterShiftMatrixFullString() <---- potentially with gui
    sendColumn()
    driveLeds()
*/

/*
    main for slave
    Led columnReceived[AMOUNT];
    initHardware()
    receiveData() -> fill in column received with inputToLed, return 1 -> expect something, return 0 -> expect nothing :)
    shiftmatrix(columnReceived)
    sendColumn()
    driveLeds()

*/
/*
int main(void)
{   
    USART3_Init();
    
    initLedPoorten();
    initGlobalVariables();
    string_brightness = 1;
    for(int i = 0; i < MAX_STRING_LEN; i++){
        string_red[i] = 0xFF;
    }
    //uarts_setup();
    //leds testing 
    
    while(1){

        //fillLedMatrixWithValue(main_matrix,20,31,0,0);
        for(int i=0;i<40;i++){
            masterShiftMatrixFullString();
            driveLeds();
        }
        
        
        
    }
}
*/
/*int main(int argc, char *argv[]) {

    Led matrix0[AMOUNT][AMOUNT];

    USART3_Init();
    //printf_P(PSTR("test\n\r\n\r\n\r"));
    //printf_P(PSTR("%s\n\r"),string);
    //printf_P(PSTR("%c\n\r"),string[0]);
    fillLedMatrixWithValue(matrix0, 31, 31, 0, 0);
    //printf_P(PSTR("Testing a matrix filled with 31 everywhere: \n\r"));
    printLedMatrixToTerminal(matrix0);

    //printf_P(PSTR("Testing letter matrix 'a': \n\r"));
    printMatrixToTerminal_P(matrix_a); //test to see if global variables are available here

    //testing master matrix shifting a full string  
    initGlobalVariables();
    getUserInput();
    //printf_P(PSTR("Testing masterShiftMatrixFullString:\n\r\n\r"));
    for(int i=0; i<40; i++) {
        masterShiftMatrixFullString();
    }

}*/


//na discord meeting op 4 april:
//bericht aan Jarne : voor het ontvangen van de data wordt eerst uint_8 array_ont[16] opgevult met de 16 ontvangen pakketjes
//daarna wordt deze gebruikt om columnreceived in te vullen met volgende code:
/*
Led columnReceived[AMOUNT]; //<- ontvangen kolom
for(int i=0;i<AMOUNT;i++) {
    inputToLed(columnReceived[I],array_ont[2i],array_ont[2i+1]); //<— invullen column received
}
shiftMatrix(columnReceived);
*/
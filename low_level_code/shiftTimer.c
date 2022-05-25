#include "../HeaderMatrix.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

/*

timer die interups geeft om de matrix te laten shiften

*/


void shiftTimer_setup(){
	 	// clk/64
	TCB0_CCMPL = 0x00;
	TCB0_CCMPH = 0x08;
	TCB0_CTRLA = 0b00000101; 
	TCB0_CTRLB = 0x00;		//periotic interupt
	TCB0_INTCTRL = 0x01;	//enable inetrups
	
	//LED voor te testen 
	PORTC_DIR |= PIN4_bm;
	PORTC_DIR |= PIN5_bm;

}


ISR(TCB0_INT_vect){
	PORTC_OUT ^= PIN5_bm;
	// shift matrix
	TCB0_INTFLAGS = 0x01;  //interupt cleren zodat timer door kan
	//stop_antwoorden = 0;
	masterShiftMatrixFullString();
	sendColumn();
	//driveLeds();
}
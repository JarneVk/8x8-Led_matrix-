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
	TCB0_CCMPH = 0x30;
	TCB0_CTRLA = 0b00000101; 
	TCB0_CTRLB = 0x00;		//periotic interupt
	TCB0_INTCTRL = 0x01;	//enable inetrups
	//TCB1_CNT = 0x00;		//zet timer op 0

	//TCB1_EVCTRL |= PIN4_bm; 	// om de timer te starten 


	//led voor testing
	PORTC_DIR |= PIN6_bm;

}


ISR(TCB0_INT_vect){
	// shift matrix
	PORTC_OUT ^= PIN6_bm;
	TCB0_INTFLAGS = 0x01;  //interupt cleren zodat timer door kan
	SendNewColumn();
	

}
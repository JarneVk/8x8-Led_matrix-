#include "../HeaderMatrix.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

/*

timer die interups geeft om de matrix te laten shiften

*/


void shiftTimer_setup(){
	TCB1_CCMPL = 0xFF;
	TCB1_CCMPH = 0xFF;
	TCB1_CTRLA = 0x01; 
	TCB1_CTRLB = 0x00;		//timeout mode
	TCB1_INTCTRL = 0x01;	//enable inetrups
	//TCB1_CNT = 0x00;		//zet timer op 0

	//TCB1_EVCTRL |= PIN4_bm; 	// om de timer te starten 


	//led voor testing
	PORTC_DIR |= PIN6_bm;

}


ISR(TCB1_INT_vect){
	// shift matrix
	PORTC_OUT ^= PIN6_bm;
	_delay_ms(1000);
	//shift_matrix();
}
/*

timer die interups geeft om de matrix te laten shiften

*/


void shiftTimer_setup(){
	//TCB1_CTRLA mag op default 0 blijven 
	TCB1_CTRLB = 0x01;		//timeout mode
	TCB1_INTCTRL = 0x01;	//enable inetrups
	TCB1_CNT = 0x00;		//zet timer op 0
	TCB1_CCMPL = 0xFF;
	TCB1_CCMPH = 0xFF;
	TCB1_EVCTRL = 0x01; 	// op 0x01 om de timer te starten 
}

ISR(TCB1_INT_vect){
	// shift matrix
}
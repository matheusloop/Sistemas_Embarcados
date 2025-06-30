/*
 * Exemple_Buttons.c
 *
 * Created: 28/06/2025 12:23:12
 * Author : Matheus
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>

#include "../../Seven_Segment_Display/Seven_Segment_Display_Lib/seven_segment_display.h"
#include "../Buttons_Lib/buttons.h"

void addNum(void* arg){
	uint8_t* num = (uint8_t*)arg;
	
	(*num)++; (*num) %= 10;
}

int main(void)
{
    /* Replace with your application code */	
	uint8_t numU = 0, numD = 0, numC = 0, numM = 0;
	
	setupButtons();
	setupSevenSegmentDisplay();
	
	register_button_callback(BUTTON_A, addNum, &numM);
	register_button_callback(BUTTON_B, addNum, &numC);
	register_button_callback(BUTTON_C, addNum, &numD);
	register_button_callback(BUTTON_D, addNum, &numU);
	
	
    while (1) {
		showAllSevenSegmentDisplay(numM, numC, numD, numU);
	}
	
}


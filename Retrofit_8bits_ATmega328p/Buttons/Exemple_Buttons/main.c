/*
 * Exemple_Buttons.c
 *
 * Created: 28/06/2025 12:23:12
 * Author : Matheus
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>

#include "../../Seven_Segment_Display/Seven_Segment_Display_Lib/seven_segment_display.h"

uint8_t numU = 0, numD = 0, numC = 0, numM = 0;


typedef enum{
	BUTTON_A = 4,
	BUTTON_B = 5,
	BUTTON_C = 6,
	BUTTON_D = 7,
} ButtonPin;

typedef void (*button_callback_t)(void* arg);

typedef struct {
	button_callback_t callback;
	void* arg;
} button_handler_t;

static volatile button_handler_t button_handlers[4] = {0};
	
void register_button_callback(ButtonPin button, button_callback_t callback, void* arg) {
	if (button >= BUTTON_A && button <= BUTTON_D) {
		button_handlers[button-4].callback = callback;
		button_handlers[button-4].arg = arg;
	}
}

void addNumU(void){
	numU++; numU %= 10;
}

void addNumD(void){
	numD++; numD %= 10;
}

void addNumC(void){
	numC++; numC %= 10;
}

void addNumM(void){
	numM++; numM %= 10;
}

// Interrupção para a porta B
ISR(PCINT0_vect){
	if(!(PINB & (1<<BUTTON_A)) && button_handlers[BUTTON_A-4].callback){       //Botão em PB4 precionado
		button_handlers[BUTTON_A-4].callback(button_handlers[BUTTON_A-4].arg);
	}
	else if (!(PINB & (1<<BUTTON_B)) && button_handlers[BUTTON_B-4].callback){ //Botão em PB5 precionado
		button_handlers[BUTTON_B-4].callback(button_handlers[BUTTON_B-4].arg);
	}
	else if (!(PINB & (1<<BUTTON_C)) && button_handlers[BUTTON_C-4].callback){ //Botão em PB6 precionado
		button_handlers[BUTTON_C-4].callback(button_handlers[BUTTON_C-4].arg);
	}
	else if (!(PINB & (1<<BUTTON_D)) && button_handlers[BUTTON_D-4].callback){ //Botão em PB7 precionado
		button_handlers[BUTTON_D-4].callback(button_handlers[BUTTON_D-4].arg);
	}
	else{}
}

void setupButtons(void){
	DDRB &= 0x0F;
	PORTB |= 0xF0;
	
	PCICR |= 0x01;
	PCMSK0 |= 0xF0;
	sei();
}

int main(void)
{
    /* Replace with your application code */	
	
	setupButtons();
	setupSevenSegmentDisplay();
	
	register_button_callback(BUTTON_A, addNumU);
	register_button_callback(BUTTON_B, addNumD);
	register_button_callback(BUTTON_C, addNumC);
	register_button_callback(BUTTON_D, addNumM);
	
	
    while (1) {
		showAllSevenSegmentDisplay(numM, numC, numD, numU);
	}
	
}


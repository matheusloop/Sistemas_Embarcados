#ifndef F_CPU	
#define F_CPU 16000000UL
#endif

#include "seven_segment_display.h"
#include <avr/io.h>
#include <util/delay.h>

static const uint8_t sevenSegmentCode[16] = {
	0x7E, 0x30, 0x6D, 0x79,
	0x33, 0x5B, 0x5F, 0x70,
	0x7F, 0x7B, 0x77, 0x1F,
	0x4E, 0x3D, 0x4F, 0x47
};

void setupSevenSegmentDisplay(void) {
	DDRC = 0xFF;   // PORTC como saída (segmentos)
	DDRB |= 0x0F;  // PB0–PB3 como saída (seleção dos dígitos)
	
	return;
}

void showSevenSegmentDisplayValue(uint8_t value, uint8_t displayAddress) {
	if (value < 16) {
		PORTC = sevenSegmentCode[value];  // Define o valor a ser mostrado
	}

	PORTB &= 0xF0;                         // Limpa PB0–PB3
	PORTB |= ((1 << displayAddress) & 0x0F); // Ativa o display desejado
	
	return;
}

void cleanSevenSegmentDisplay(void) {
	PORTB &= 0xF0;  // Limpa PB0–PB3
	
	return;
}

void showAllSevenSegmentDisplay(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3) {
	
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_0, 0);
	_delay_ms(2);

	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_1, 1);
	_delay_ms(2);
	
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_2, 2);
	_delay_ms(2);
	
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_3, 3);
	_delay_ms(2);
	
	return;
}

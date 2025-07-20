#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "seven_segment_display.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Tabela com os códigos binários dos segmentos (a–g) para os valores 0–F
static const uint8_t sevenSegmentCode[16] = {
	0x7E, // 0
	0x30, // 1
	0x6D, // 2
	0x79, // 3
	0x33, // 4
	0x5B, // 5
	0x5F, // 6
	0x70, // 7
	0x7F, // 8
	0x7B, // 9
	0x77, // A
	0x1F, // B
	0x4E, // C
	0x3D, // D
	0x4F, // E
	0x47  // F
};

// Variáveis globais para controle dos displays
static uint8_t actualDisplay = 0;
static uint8_t displaysValues[4] = {0, 0, 0, 0};

void setupSevenSegmentDisplay(void) {
	// Define PORTD (segmentos a–g) como saída
	DDRD |= 0x7F;   // PD0–PD6 como saída
	// Define PORTB (seleção dos dígitos) como saída
	DDRB |= 0x0F;   // PB0–PB3 como saída
}

void showSevenSegmentDisplayValue(uint8_t value, uint8_t displayAddress) {
	// Limpa os bits dos segmentos (PD0–PD6)
	PORTD &= 0x80;

	if (value < 16) {
		// Define os segmentos conforme o valor
		PORTD |= sevenSegmentCode[value];
	}

	// Limpa seleção anterior de dígito (PB0–PB3)
	PORTB &= 0xF0;

	// Ativa apenas o dígito especificado
	PORTB |= ((1 << displayAddress) & 0x0F);
}

void cleanSevenSegmentDisplay(void) {
	// Desativa todos os dígitos (PB0–PB3)
	PORTB &= 0xF0;
}

// Rotina de interrupção do Timer0 - Multiplexação dos displays
ISR(TIMER0_OVF_vect) {
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(displaysValues[actualDisplay], actualDisplay);
	
	// Próximo display
	actualDisplay = (actualDisplay + 1) % 4;
}

void showAllSevenSegmentDisplay(void) {
	// Configura Timer0 em modo normal
	TCCR0A = 0b00000000;

	// Prescaler = 256 → Overflow a cada ~4ms (256 * 256 / 16MHz)
	TCCR0B = 0b00000100;

	// Habilita interrupção por overflow do Timer0
	TIMSK0 = 0b00000001;

	// Habilita interrupções globais
	sei();
}

void setAllSevenSegmentDisplayValues(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3) {
	displaysValues[0] = valueDisp_0;
	displaysValues[1] = valueDisp_1;
	displaysValues[2] = valueDisp_2;
	displaysValues[3] = valueDisp_3;
}

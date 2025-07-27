#include <avr/io.h>
#include <avr/interrupt.h>

#include "seven_segment_display.h"

// Tabela com os códigos binários dos segmentos (a–g) para representar os valores de 0 a F em hexadecimal
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
	// Define os pinos PC0–PC3 como saída para os segmentos A, B, C e D
	DDRC |= (1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3);
	
	// Define os pinos PB1–PB3 como saída para os segmentos E, F e G
	DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3);
	
	// Define os pinos PD2, PD3, PD4 e PD7 como saída para habilitação dos displays (EN0 a EN3)
	DDRD |= (1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD7);
}

void activeSegments(uint8_t segmentCode) {
	// Ativa os segmentos com base no valor binário fornecido
	if (segmentCode & (1<<6)) PORTC |= (1<<PORTC0); // Segmento A
	if (segmentCode & (1<<5)) PORTC |= (1<<PORTC1); // Segmento B
	if (segmentCode & (1<<4)) PORTC |= (1<<PORTC2); // Segmento C
	if (segmentCode & (1<<3)) PORTC |= (1<<PORTC3); // Segmento D
	if (segmentCode & (1<<2)) PORTB |= (1<<PORTB1); // Segmento E
	if (segmentCode & (1<<1)) PORTB |= (1<<PORTB2); // Segmento F
	if (segmentCode & (1<<0)) PORTB |= (1<<PORTB3); // Segmento G
}

void cleanSevenSegmentDisplay(void) {
	// Desliga todos os segmentos
	PORTC &= ~((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3)); // Segmentos A–D
	PORTB &= ~((1<<PORTB1) | (1<<PORTB2) | (1<<PORTB3));               // Segmentos E–G
	
	// Desabilita todos os displays
	PORTD &= ~((1<<PORTD2) | (1<<PORTD3) | (1<<PORTD4) | (1<<PORTD7));
}

void showSevenSegmentDisplayValue(uint8_t value, uint8_t displayAddress) {
	// Limpa todos os segmentos e displays antes de exibir novo valor
	cleanSevenSegmentDisplay();

	// Ativa os segmentos correspondentes ao valor (0–F)
	if (value < 16) {
		activeSegments(sevenSegmentCode[value]);
	}

	// Habilita o display correspondente ao endereço fornecido
	switch(displayAddress){
		case 0:
			PORTD |= (1<<PORTD2); // Habilita display 0
			break;
		case 1:
			PORTD |= (1<<PORTD3); // Habilita display 1
			break;
		case 2:
			PORTD |= (1<<PORTD4); // Habilita display 2
			break;
		case 3:
			PORTD |= (1<<PORTD7); // Habilita display 3
			break;
		default:
			break; // Endereço inválido: nenhum display é habilitado
	}
}

// Rotina de interrupção do Timer2 – Multiplexação dos displays
ISR(TIMER2_OVF_vect) {
	// Exibe o valor correspondente ao display atual
	showSevenSegmentDisplayValue(displaysValues[actualDisplay], actualDisplay);
	
	// Avança para o próximo display (multiplexação cíclica)
	actualDisplay = (actualDisplay + 1) % 4;
}

void showAllSevenSegmentDisplay(void) {
	// Configura o Timer2 para modo normal e prescaler de 256 (~4ms entre overflows)
	TCCR2A = 0x00;						//Modo de operação normal
	TCCR2B |= (1<<CS22);                // Prescaler = 256
	TIMSK2 |= (1<<TOIE2);               // Habilita interrupção por overflow do Timer2
	sei();                              // Habilita interrupções globais
}

void setAllSevenSegmentDisplayValues(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3) {
	// Define os valores a serem exibidos em cada display (0–3)
	displaysValues[0] = valueDisp_0;
	displaysValues[1] = valueDisp_1;
	displaysValues[2] = valueDisp_2;
	displaysValues[3] = valueDisp_3;
}

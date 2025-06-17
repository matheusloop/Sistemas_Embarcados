#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "../Seven_Segment_Display_Lib/seven_segment_display.h"

void setupSevenSegmentDisplay() {
	DDRC = 0xFF;   // PORTC como saída (segmentos)
	DDRB |= 0x0F;  // PB0–PB3 como saída (seleção dos dígitos)
	
	return;
}

void showSevenSegmentDisplayValue(uint8_t value, uint8_t displayAdress){
	const uint8_t sevenSegmentCode[16] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47};  // Segmentos para 0–F
		
	if (value < 16) {
		PORTC = sevenSegmentCode[value]; // Define o valor a ser mostrado
	}
	
	//Mostra o valor
	PORTB &= 0xF0;  // Limpa PB0–PB3
	PORTB |= ((1 << displayAdress) & 0x0F);  // Ativa o display desejado
	
	return;
}

void cleanSevenSegmentDisplay() {
	PORTB &= 0xF0;  // Limpa PB0–PB3
	
	return;
}

void showAllSevenSegmentDisplay(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3) {
	
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_0, 0);
		
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_1, 1);
		
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_2, 2);
		
	cleanSevenSegmentDisplay();
	showSevenSegmentDisplayValue(valueDisp_3, 3);
	
	return;
}

// ========================
// FUNÇÃO PRINCIPAL
// ========================

int main(void){
	uint16_t num0 = 0, num1 = 0;
	setupSevenSegmentDisplay();  // Inicializa os pinos do display de 7 segmentos

	while(1){
		/**/
		showAllSevenSegmentDisplay((num1)%10, (num1+1)%10, (num1+2)%10, (num1+3)%10);
		
		num0++;
		num1 = (num0/1000)%10;
		
		//showAllSevenSegmentDisplay(0xC, 0xA, 0xF, 0xE);

	}
	return 0;
}

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "../seg7display/seg7display.h"

void setupSeg7Display() {
	DDRC = 0xFF;   // PORTC como saída (segmentos)
	DDRB |= 0x0F;  // PB0–PB3 como saída (seleção dos dígitos)
	
	return;
}

void changeSeg7DisplayValue(uint8_t value) {
	uint8_t LUT[10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};  // Segmentos para 0–9
	if (value < 10) {
		PORTC = LUT[value];
	}
	
	return;
}

void enableSeg7Display(uint8_t displayAdress) {
	PORTB &= 0xF0;  // Limpa PB0–PB3
	PORTB |= ((1 << displayAdress) & 0x0F);  // Ativa o dígito desejado
	
	return;
}

void cleanSeg7Display() {
	PORTB &= 0xF0;  // Limpa PB0–PB3
	
	return;
}

void runSeg7Display(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3) {
	
	cleanSeg7Display();
	changeSeg7DisplayValue(valueDisp_0);
	enableSeg7Display(0);
	
	cleanSeg7Display();
	changeSeg7DisplayValue(valueDisp_1);
	enableSeg7Display(1);
	
	cleanSeg7Display();
	changeSeg7DisplayValue(valueDisp_2);
	enableSeg7Display(2);
	
	cleanSeg7Display();
	changeSeg7DisplayValue(valueDisp_3);
	enableSeg7Display(3);
	
	return;
}

// ========================
// FUNÇÃO PRINCIPAL
// ========================

int main(void){
	uint32_t num = 0;
	setupSeg7Display();  // Inicializa os pinos do display de 7 segmentos

	while(1){
		
		// Atualiza o display com os valores atuais
		runSeg7Display((num/100000)%10, (num/10000)%10, (num/1000)%10, (num/100)%10);
		
		num++;
		
	}
	return 0;
}

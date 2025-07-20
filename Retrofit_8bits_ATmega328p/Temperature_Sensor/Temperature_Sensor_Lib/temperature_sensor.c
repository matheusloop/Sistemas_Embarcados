#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t TemperatureSensorLevel = 0;

ISR(ADC_vect){
	TemperatureSensorLevel = ADC;
}

void setupTemperatureSensor(void){
	DDRC  &= ~(1<<5); // Configura o pino PC5 como entrada
	PORTC &= ~(1<<5); // Desabilita o pull-up interno do pino PC5
	
	ADMUX = 0b01000101; // Usa VCC como referência (AVCC), seleciona canal ADC5 (PC5)
	ADCSRA = 0b11101111; // Habilita ADC, interrupção, conversão contínua e prescaler de 128
	ADCSRB = 0x00; // Configura modo de conversão contínua
	DIDR0 = 0b00011111; // Desabilita o buffer digital do pino PC5
	sei(); // Habilita interrupções globais
}

uint16_t readTemperatureSensorLevel(void){
	return TemperatureSensorLevel;
}

uint16_t readTemperatureDegrees(void){
	return  (TemperatureSensorLevel-120)/8; // Converte o nível ADC em graus Celsius (ajuste empírico)
}

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t TemperatureSensorValue = 0;

ISR(ADC_vect){
	TemperatureSensorValue = ADC;
}

void setupTemperatureSensor(void){
	DDRC  &= ~(1<<5); //Porta C5 como entrada
	PORTC &= ~(1<<5); //Desabilita o pullup do PC0
	
	ADMUX = 0b01000101; //Define fundo de escala de 5V (VCC), ADC5
	ADCSRA = 0b11101111; //habilita o AD, habilita interrupção, modo de conversão contínua, prescaler = 128
	ADCSRB = 0x00; //modo de conversão contínua
	DIDR0 = (1<<ADC5D); //Desabilita o Buffer digital do PC5
}

uint16_t readTemperatureSensor(void){
	return TemperatureSensorValue;
}
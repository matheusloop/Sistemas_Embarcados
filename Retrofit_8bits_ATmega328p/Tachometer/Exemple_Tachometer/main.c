#define F_CPU 16000000UL
#include "../../Heating_Cooling_System/Heating_Cooling_System_Lib/heating_cooling_system.h"
#include "../../Temperature_Sensor/UART_Lib/UART_Lib.h"


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Variáveis globais
uint16_t tempo_borda_subida = 0, tempo_delta = 0;

ISR(TIMER1_CAPT_vect){ //interrupção por captura do valor do TC1{
	 if(TCCR1B & (1<<ICES1))//lê o valor de contagem do TC1 na borda de subida do sinal
	 tempo_borda_subida = ICR1;//salva a primeira contagem para determinar a largura do pulso
	 else//lê o valor de contagem do TC1 na borda de descida do sinal
	 tempo_delta = (ICR1- tempo_borda_subida)*16; //cada incremento do TC1 corresponde a 16us
	 TCCR1B ^= (1<<ICES1); //inverte a borda de captura
}

int main(void){
	
	setupUART(MYUBRR);
	setupHeatingCoolingSystem();
	
	//Configura GPIO
	DDRB &= 0b11111110;// Entrada no pino PB0 (Captura no PB0 (ICP1))
	PORTB |= 0b00000001;// Pullups PB0 ativo
	
	//Configura Timer
	TCCR1B = (1<<ICES1)|(1<<CS12);//Captura na borda de subida, TC1 com prescaler = 256.
	//Estouro a cada 256*(2^16)/16MHz = (2^16)*16us = 1,04s
	TIMSK1 = 1<<ICIE1;//habilita a interrupção por captura
	sei(); //Habilita o flag de interrupções globais
	
	setCoolerDutyCycle(50);
	
	while (1){
		sendASCIIFromInt(tempo_delta);
		_delay_ms(1000);
	}
}
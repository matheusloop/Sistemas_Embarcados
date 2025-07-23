#include "../../Temperature_Sensor/UART_Lib/UART_Lib.h"
#include "../../Heating_Cooling_System/Heating_Cooling_System_Lib/heating_cooling_system.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Variáveis globais
uint16_t tempo_borda_subida = 0;

ISR(TIMER1_CAPT_vect){ //interrupção por captura do valor do TC1{
	
	tempo_borda_subida = ICR1;//salva a primeira contagem para determinar a largura do pulso
	ICR1 = 0;
}
//Função para envio de um frame de 5 a 8bits
int main(void){
	
	setupUART(MYUBRR);
	setCoolerDutyCycle(50);
	//Configura GPIO
	DDRB &= 0b11111110;// Entrada no pino PB0 (Captura no PB0 (ICP1))
	PORTB |= 0b00000001;// Pullups PB0 ativo
	
	TCCR1B = (1<<ICES1)|(1<<CS12);//Captura na borda de subida, TC1 com prescaler = 256.
	//Estouro a cada 256*(2^16)/16MHz = (2^16)*16us = 1,04s
	TIMSK1 = 1<<ICIE1;//habilita a interrupção por captura
	sei(); //Habilita o flag de interrupções globais
	
	
	while (1){
		sendASCIIFromInt(tempo_borda_subida);
		_delay_ms(1000);
	}
}
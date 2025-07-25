#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t ultima_captura = 0;
volatile uint32_t velRPM = 0;

ISR(TIMER1_CAPT_vect){
	uint16_t dif_bordas = 0, captura_atual = 0;
	uint32_t T_ciclo = 0;

	captura_atual = ICR1;
	dif_bordas = captura_atual - ultima_captura;
	ultima_captura = captura_atual;

	T_ciclo = (uint32_t)dif_bordas * 16; // 16 us por incremento com prescaler 256

	velRPM = 60000000UL / (7 * T_ciclo); // 7 pulsos por volta

}

void setupTachometer(){
	DDRB &= ~(1 << DDB0);    // PB0 como entrada
	PORTB |= (1 << PORTB0);  // Pull-up ativado

	TCCR1B = (1 << ICES1) | (1 << CS12); // Captura na subida, prescaler 256
	TIMSK1 = (1 << ICIE1);               // Habilita interrupção por captura

	sei(); // Interrupções globais
}

uint32_t getTachometerVelValue(void){
	return velRPM;
}

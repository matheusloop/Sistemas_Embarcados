#include <avr/io.h>
#include <avr/interrupt.h>

#include "heating_cooling_system.h"

// Variável global para armazenar o valor lido do sensor de temperatura (nível ADC)
uint16_t TemperatureSensorLevel = 0;

// Rotina de interrupção do ADC – chamada automaticamente após cada conversão
ISR(ADC_vect){
	// Armazena o valor lido do conversor analógico-digital (ADC)
	TemperatureSensorLevel = ADC;
}

// Variáveis globais voláteis usadas na ISR e na leitura da velocidade
volatile uint16_t ultima_captura = 0; // Armazena o valor da última borda capturada
volatile uint32_t velRPM = 0;         // Armazena o valor calculado da velocidade em RPM

// Rotina de interrupção do Timer1 para captura de bordas do Tacômetro (entrada de tacômetro no PB0)
ISR(TIMER1_CAPT_vect){
	uint16_t dif_bordas = 0, captura_atual = 0;
	uint32_t T_ciclo = 0;

	captura_atual = ICR1;                        // Lê o valor atual capturado (momento da borda)
	dif_bordas = captura_atual - ultima_captura; // Calcula o intervalo entre esta borda e a anterior
	ultima_captura = captura_atual;              // Atualiza o valor da última captura

	T_ciclo = (uint32_t)dif_bordas * 16;         // Converte a diferença de contagem para tempo em microssegundos (16 us por tick)

	velRPM = 60000000UL / (7 * T_ciclo);         // Calcula a velocidade em RPM (7 pulsos por volta)
}

void setupHeatingCoolingSystem(void){
	/*-----------------------------------------------------------------*/
	/*-----------------SETUP AQUECEDOR E RESFRIADOR--------------------*/
	/*-----------------------------------------------------------------*/
	// Configura os pinos PD5 (OC0B – resfriador) e PD6 (OC0A – aquecedor) como saídas digitais
	DDRD |= (1 << DDD5) | (1 << DDD6);

	// Configura o Timer0 no modo Fast PWM com TOP fixo em 0xFF
	// Canal A (OC0A – PD6) e Canal B (OC0B – PD5) em modo de saída não-invertido:
	// COM0A1:0 = 0b10   OC0A ativo com duty cycle direto
	// COM0B1:0 = 0b10   OC0B ativo com duty cycle direto
	// WGM02:0  = 0b011  Fast PWM, TOP = 0xFF
	// FOC0A:B  = 0b00   Desabilita modo de comparação forçada
	// CS02:0   = 0b011  Prescaler = 64  Freq. ~976 Hz (T ? 1ms)
	TCCR0A |= (1<<COM0A1) | (0<<COM0A0) | (1<<COM0B1) | (0<<COM0B0) | (1<<WGM01) | (1<<WGM00);
	TCCR0B |= (0<<FOC0A)  | (0<<FOC0B)  | (0<<WGM02)  | (0<<CS02)   | (1<<CS01)  | (1<<CS00);

	// Inicializa os dois canais com 0% de duty cycle (desligados)
	OCR0A = 0; // Resfriador (canal A – PD6)
	OCR0B = 0; // Aquecedor (canal B – PD5)
	
	
	/*-----------------------------------------------------------------*/
	/*-----------------SETUP SENSOR DE TEMPERATURA---------------------*/
	/*-----------------------------------------------------------------*/
	// Configura o pino PC5 como entrada (canal ADC5)
	DDRC  &= ~(1<<DDC5);      // PC5 como entrada
	PORTC &= ~(1<<PORTC5);    // Desativa o resistor de pull-up interno do PC5

	// Configura o ADC:
	// - Referência de tensão em AVCC (VCC com capacitor em AREF)
	// - Resultado à direita (ADLAR = 0)
	// - Seleciona canal de entrada ADC5 (PC5)
	ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (0<<MUX3) | (1<<MUX2) | (0<<MUX1) | (1<<MUX0);

	// Configura o registrador ADCSRA:
	// - Habilita o ADC
	// - Inicia a conversão
	// - Habilita modo de conversão automática contínua (free running mode)
	// - Habilita interrupção do ADC
	// - Define prescaler para 128 (frequência do ADC = F_CPU / 128)
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (0<<ADIF) | (1<<ADIE) |(1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADCSRB = 0x00; // Define o modo de operação do ADC como “free running” (modo contínuo)
	DIDR0 |= (1<<ADC5D); // Desativa o buffer digital do pino PC5 para economizar energia


	/*-----------------------------------------------------------------*/
	/*------------------------SETUP TACÔMETRO--------------------------*/
	/*-----------------------------------------------------------------*/
	// Configura o tacômetro utilizando o Timer1 em modo de captura
	DDRB &= ~(1 << DDB0);    // Configura PB0 (ICP1) como entrada digital
	PORTB |= (1 << PORTB0);  // Ativa resistor de pull-up interno para PB0

	// Configura Timer1:
	// ICES1 = 1  captura na borda de subida
	// CS12:0 = 0b100  prescaler = 256
	TCCR1B = (1 << ICES1) | (1 << CS12);
	TIMSK1 = (1 << ICIE1);               // Habilita interrupção de captura do Timer1 (ICIE1)
	sei();                               // Habilita interrupções globais
}

// Ajusta o duty cycle do aquecedor com base no valor percentual (0–100%)
void setHeaterDutyCycle(uint8_t heaterDutyCycle){
	OCR0B = (255 * (uint16_t)heaterDutyCycle) / 100;
}

// Ajusta o duty cycle do resfriador com base no valor percentual (0–100%)
void setCoolerDutyCycle(uint8_t coolerDutyCycle){
	OCR0A = (255 * (uint16_t)coolerDutyCycle) / 100;
}

uint16_t getTemperatureSensorLevel(void){
	// Retorna o valor bruto do ADC armazenado (nível analógico do sensor)
	return TemperatureSensorLevel;
}

uint16_t getTemperatureDegrees(void){
	// Converte o valor do ADC em graus Celsius com base em ajuste empírico
	// Fórmula aproximada: Temperatura (°C) = (ADC - 120) / 8
	return (TemperatureSensorLevel - 120) / 8;
}

// Retorna a última velocidade medida em RPM
uint32_t getTachometerVelValue(void){
	return velRPM;
}

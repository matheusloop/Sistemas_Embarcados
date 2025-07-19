#define F_CPU 16000000UL//Frequência de trabalho da CPU
#define BAUD 9600//Taxa da UART
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint16_t leitura_ADC = 0;

// ||Função para inicialização da USART||
void UART_Init(uint16_t ubrr){
	
	UBRR0H = (uint8_t)(ubrr>>8); //Ajusta a taxa de transmissão
	UBRR0L = (uint8_t)ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita o transmissor e o receptor
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); //Ajusta o formato do frame: 8 bits de dados e 2 de parada
}

// ||Função para envio de um frame de 5 a 8bits||
void UART_Transmit(uint8_t data){

	while(!( UCSR0A & (1<<UDRE0)));//Espera a limpeza do registrador de transmissão
	UDR0 = data; //Coloca o dado no registrador e o envia
}

// ||Função para recepção de um frame de 5 a 8bits||
uint8_t UART_Receive(void)
{
	while(!(UCSR0A & (1<<RXC0))); //Espera o dado ser recebido
	return UDR0; //Lê o dado recebido e retorna
}

void sendASCII(uint16_t num) {
	uint16_t divisor = 10000;

	for (int i = 0; i < 5; i++) {
		uint8_t digit = (num / divisor) % 10;
		UART_Transmit('0' + digit);
		_delay_ms(2);
		divisor /= 10;
	}
	
	UART_Transmit('\n');
}


ISR(ADC_vect){
	uint16_t = temp;
	leitura_ADC = ADC;
	
	temp = (1/8)*leitura_ADC + 0.837;

	sendASCII(temp);
}

 int main(void){
	 
	UART_Init(MYUBRR);
	 
	//GPIO
	DDRC  &= ~(1<<0); //Porta C0 como entrada
	PORTC &= ~(1<<0); //Desabilita o pullup do PC0

	//Configura ADC
	ADMUX = 0b01000000; //Tensão interna de ref (1.1V), canal 0
	ADCSRA = 0b11101111; //habilita o AD, habilita interrupção, modo de conversão contínua, prescaler = 128
	ADCSRB = 0x00; //modo de conversão contínua
	DIDR0 = 0b00111110; //habilita pino PC0 como entrada do ADC0
	sei();

	DDRD |= (1<<2);
	PORTD |= (1<<2);


	while(1){
		PORTD ^= (1<<2);
		_delay_ms(500);
	}
	 
	return 0;
 }
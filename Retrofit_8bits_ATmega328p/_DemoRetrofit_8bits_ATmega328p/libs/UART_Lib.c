#ifndef F_CPU
#define F_CPU 16000000UL  // Define a frequência da CPU como 16 MHz
#endif

#ifndef BAUD
#define BAUD 9600         // Define a taxa de transmissão (baud rate) da UART
#endif

#ifndef MYUBRR
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1)  // Calcula o valor do registrador UBRR com base na frequência e baud rate
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "UART_Lib.h"

// Inicializa a UART com o valor fornecido para o registrador UBRR
void setupUART() {
	UBRR0H = (uint8_t)((MYUBRR) >> 8);         // Configura os 8 bits mais significativos de UBRR0
	UBRR0L = (uint8_t)MYUBRR;                  // Configura os 8 bits menos significativos de UBRR0
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);      // Habilita recepção e transmissão
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);     // Define 2 bits de parada e 8 bits de dados
}

// Envia um byte (8 bits) pela UART
void transmitUART_8bits(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));     // Aguarda o registrador de dados estar vazio
	UDR0 = data;                          // Escreve o dado no registrador de transmissão
}

// Envia dois bytes (16 bits) pela UART, MSB primeiro
void transmitUART_16bits(uint16_t data) {
	transmitUART_8bits((uint8_t)(data >> 8));        // Envia os 8 bits mais significativos
	transmitUART_8bits((uint8_t)data);               // Envia os 8 bits menos significativos
}

// Recebe um byte (8 bits) pela UART (modo bloqueante)
uint8_t receiveUART(void) {
	while (!(UCSR0A & (1 << RXC0)));    // Aguarda até que um dado seja recebido
	return UDR0;                        // Retorna o dado recebido
}

// Envia um número inteiro sem sinal (uint16_t) como caracteres ASCII pela UART
void sendASCIIFromInt(uint16_t num) {
	char buffer[6];                         // Buffer para armazenar a representação em ASCII (até 5 dígitos + nulo)
	utoa(num, buffer, 10);                  // Converte o número para string decimal
	for (char *p = buffer; *p; p++) {
		transmitUART_8bits(*p);             // Envia cada caractere da string
		_delay_ms(2);                       // Pequeno atraso entre caracteres (evita sobrecarga em alguns receptores)
	}
}

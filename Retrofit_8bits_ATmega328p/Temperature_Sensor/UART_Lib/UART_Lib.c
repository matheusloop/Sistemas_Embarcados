#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "UART_Lib.h"

// Inicializa UART com o valor UBRR configurado
void setupUART(uint16_t ubrr) {
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

// Envia um byte pela UART
void transmitUART_8bits(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0))); // Aguarda registrador vazio
	UDR0 = data;
}

// Envia dois bytes (16 bits) pela UART
void transmitUART_16bits(uint16_t data) {
	transmitUART_8bits((uint8_t)(data >> 8)); // MSB
	transmitUART_8bits((uint8_t)data);        // LSB
}

// Recebe um byte pela UART (bloqueante)
uint8_t receiveUART(void) {
	while (!(UCSR0A & (1 << RXC0))); // Aguarda dado recebido
	return UDR0;
}

// Envia número inteiro como string ASCII pela UART
void sendASCIIFromInt(uint16_t num) {
	char buffer[6];
	itoa(num, buffer, 10);
	for (char *p = buffer; *p; p++) {
		transmitUART_8bits(*p);
		_delay_ms(2);
	}
	transmitUART_8bits('\n');
}

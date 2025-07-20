#ifndef UART_LIB_H
#define UART_LIB_H

#ifndef F_CPU
#define F_CPU 16000000UL  // Frequência da CPU
#endif

#ifndef BAUD
#define BAUD 9600         // Baud rate da UART
#endif

#ifndef MYUBRR
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1)  // Valor do registrador UBRR
#endif

#include <avr/io.h>
#include <stdint.h>

/**
 * @brief Inicializa a UART com a taxa de transmissão especificada pelo UBRR.
 * 
 * Configura os registradores da UART para comunicação serial,
 * habilitando transmissor e receptor, com formato de frame padrão:
 * 8 bits de dados, 2 bits de parada.
 * 
 * @param ubrr Valor do registrador UBRR para ajustar a baud rate.
 */
void setupUART(uint16_t ubrr);

/**
 * @brief Envia um dado de 8 bits pela UART.
 * 
 * A função aguarda até que o registrador de transmissão esteja vazio
 * para colocar o dado no registrador de transmissão.
 * 
 * @param data Byte a ser enviado.
 */
void transmitUART_8bits(uint8_t data);

/**
 * @brief Envia um dado de 16 bits pela UART.
 * 
 * O dado é enviado em duas partes, primeiro o byte mais significativo,
 * seguido pelo byte menos significativo.
 * 
 * @param data Palavra de 16 bits a ser enviada.
 */
void transmitUART_16bits(uint16_t data);

/**
 * @brief Recebe um dado de 8 bits pela UART.
 * 
 * A função bloqueia até que um dado seja recebido no registrador de recepção.
 * 
 * @return uint8_t Byte recebido pela UART.
 */
uint8_t receiveUART(void);

/**
 * @brief Envia um número inteiro (uint16_t) como uma string ASCII pela UART.
 * 
 * A função converte o número em sua representação decimal ASCII e envia
 * caractere por caractere, seguido de um caractere de nova linha ('\n').
 * 
 * @param num Número inteiro a ser enviado como string ASCII.
 */
void sendASCIIFromInt(uint16_t num);

#endif // UART_LIB_H

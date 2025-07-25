#ifndef UART_LIB_H
#define UART_LIB_H

/**
 * @brief Inicializa a UART com o valor fornecido para o registrador UBRR.
 *
 * Configura os registradores da UART para comunicação serial:
 * - Habilita recepção e transmissão
 * - Define 8 bits de dados e 2 bits de parada
 *
 * @param ubrr Valor do registrador UBRR para definir a taxa de transmissão.
 */
void setupUART();

/**
 * @brief Envia um byte (8 bits) pela UART.
 *
 * Aguarda até que o registrador de dados esteja pronto e, em seguida,
 * envia o dado através da UART.
 *
 * @param data Byte a ser transmitido.
 */
void transmitUART_8bits(uint8_t data);

/**
 * @brief Envia uma palavra de 16 bits pela UART.
 *
 * O dado é enviado em dois bytes:
 * - Primeiro os 8 bits mais significativos (MSB)
 * - Depois os 8 bits menos significativos (LSB)
 *
 * @param data Valor de 16 bits a ser transmitido.
 */
void transmitUART_16bits(uint16_t data);

/**
 * @brief Recebe um byte (8 bits) pela UART.
 *
 * Aguarda de forma bloqueante até que um dado seja recebido e retorna
 * o conteúdo do registrador de recepção.
 *
 * @return Byte recebido via UART.
 */
uint8_t receiveUART(void);

/**
 * @brief Envia um número inteiro sem sinal (uint16_t) como string ASCII pela UART.
 *
 * Converte o número para a representação decimal em ASCII e envia
 * caractere por caractere pela UART.
 *
 * @param num Número a ser convertido e enviado como texto.
 */
void sendASCIIFromInt(uint16_t num);

#endif // UART_LIB_H
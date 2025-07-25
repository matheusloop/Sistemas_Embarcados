#ifndef TACHOMETER_H
#define TACHOMETER_H

#include <avr/io.h>

/**
 * @brief Inicializa o tac�metro usando o Timer1 em modo de captura (ICP1).
 * 
 * Configura o pino PB0 como entrada com pull-up e o Timer1 para capturar bordas
 * de subida com prescaler de 256. Tamb�m habilita a interrup��o de captura e
 * ativa as interrup��es globais.
 * 
 * @note Esta fun��o deve ser chamada uma �nica vez no in�cio do programa.
 */
void setupTachometer(void);

/**
 * @brief Retorna o valor atual da velocidade de rota��o em RPM.
 * 
 * A velocidade � calculada a partir do tempo entre bordas sucessivas de um 
 * sinal de entrada conectado ao pino ICP1 (PB0). Assumem-se 7 pulsos por rota��o.
 * 
 * @return uint32_t Velocidade em rota��es por minuto (RPM).
 */
uint32_t getTachometerVelValue(void);

#endif // TACHOMETER_H

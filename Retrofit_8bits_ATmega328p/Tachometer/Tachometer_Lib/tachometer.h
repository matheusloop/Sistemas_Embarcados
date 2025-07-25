#ifndef TACHOMETER_H
#define TACHOMETER_H

#include <avr/io.h>

/**
 * @brief Inicializa o tacômetro usando o Timer1 em modo de captura (ICP1).
 * 
 * Configura o pino PB0 como entrada com pull-up e o Timer1 para capturar bordas
 * de subida com prescaler de 256. Também habilita a interrupção de captura e
 * ativa as interrupções globais.
 * 
 * @note Esta função deve ser chamada uma única vez no início do programa.
 */
void setupTachometer(void);

/**
 * @brief Retorna o valor atual da velocidade de rotação em RPM.
 * 
 * A velocidade é calculada a partir do tempo entre bordas sucessivas de um 
 * sinal de entrada conectado ao pino ICP1 (PB0). Assumem-se 7 pulsos por rotação.
 * 
 * @return uint32_t Velocidade em rotações por minuto (RPM).
 */
uint32_t getTachometerVelValue(void);

#endif // TACHOMETER_H

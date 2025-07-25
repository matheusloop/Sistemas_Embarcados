#ifndef HEATING_COOLING_SYSTEM_H
#define HEATING_COOLING_SYSTEM_H

#include <avr/io.h>

/**
* @brief Inicializa o sistema de controle do aquecedor e resfriador via PWM.
*
* - Configura os pinos PD6 (OC0A) e PD5 (OC0B) como sa�da.
* - Ativa o modo Fast PWM no Timer0 (TOP = 0xFF).
* - Define OC0A e OC0B em modo n�o-invertido.
* - Usa prescaler de 64 (frequ�ncia de PWM ~976 Hz).

* @brief Inicializa o tac�metro usando o Timer1 em modo de captura (ICP1).
*
* Configura o pino PB0 como entrada com pull-up e o Timer1 para capturar bordas
* de subida com prescaler de 256. Tamb�m habilita a interrup��o de captura e
* ativa as interrup��es globais.

* @brief Configura o ADC para leitura cont�nua do sensor de temperatura.
*
* - Canal utilizado: ADC5 (pino PC5)
* - Refer�ncia de tens�o: AVCC (5V)
* - Modo: Convers�o cont�nua (Free Running Mode)
* - Interrup��o: Ativada (resultado armazenado automaticamente)
* - Prescaler: 128 (para frequ�ncia adequada do ADC)
*
* Esta fun��o tamb�m desativa o buffer digital no pino de entrada para economia de energia.
*/
void setupHeatingCoolingSystem(void);

/**
 * @brief Define o duty cycle (0�100%) do aquecedor.
 *
 * Controla a sa�da PWM no pino PD6 (OC0A).
 *
 * @param heaterDutyCycle Valor percentual de 0 a 100.
 */
void setHeaterDutyCycle(uint8_t heaterDutyCycle);

/**
 * @brief Define o duty cycle (0�100%) do resfriador.
 *
 * Controla a sa�da PWM no pino PD5 (OC0B).
 *
 * @param coolerDutyCycle Valor percentual de 0 a 100.
 */
void setCoolerDutyCycle(uint8_t coolerDutyCycle);

/**
 * @brief Retorna o valor bruto da �ltima leitura do sensor de temperatura.
 *
 * O valor retornado � o resultado da convers�o anal�gica-digital (ADC), com resolu��o de 10 bits (0�1023),
 * proporcional � tens�o de entrada no pino PC5 (canal ADC5).
 *
 * @return uint16_t Valor atual do ADC (n�vel anal�gico do sensor)
 */
uint16_t getTemperatureSensorLevel(void);

/**
 * @brief Converte o valor do ADC em temperatura em graus Celsius.
 *
 * A convers�o � baseada na equa��o:
 *    Temperatura (�C) = (ADC - 120) / 8
 *
 * Esta f�rmula foi ajustada empiricamente para sensores como o LM35,
 * assumindo alimenta��o de 5V (AVCC) e resposta linear de 10 mV/�C.
 *
 * @return uint16_t Temperatura aproximada em graus Celsius
 */
uint16_t getTemperatureDegrees(void);

/**
 * @brief Retorna o valor atual da velocidade de rota��o em RPM.
 * 
 * A velocidade � calculada a partir do tempo entre bordas sucessivas de um 
 * sinal de entrada conectado ao pino ICP1 (PB0). Assumem-se 7 pulsos por rota��o.
 * 
 * @return uint32_t Velocidade em rota��es por minuto (RPM).
 */
uint32_t getTachometerVelValue(void);

#endif // HEATING_COOLING_SYSTEM_H

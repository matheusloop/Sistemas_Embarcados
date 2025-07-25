#ifndef HEATING_COOLING_SYSTEM_H
#define HEATING_COOLING_SYSTEM_H

#include <avr/io.h>

/**
* @brief Inicializa o sistema de controle do aquecedor e resfriador via PWM.
*
* - Configura os pinos PD6 (OC0A) e PD5 (OC0B) como saída.
* - Ativa o modo Fast PWM no Timer0 (TOP = 0xFF).
* - Define OC0A e OC0B em modo não-invertido.
* - Usa prescaler de 64 (frequência de PWM ~976 Hz).

* @brief Inicializa o tacômetro usando o Timer1 em modo de captura (ICP1).
*
* Configura o pino PB0 como entrada com pull-up e o Timer1 para capturar bordas
* de subida com prescaler de 256. Também habilita a interrupção de captura e
* ativa as interrupções globais.

* @brief Configura o ADC para leitura contínua do sensor de temperatura.
*
* - Canal utilizado: ADC5 (pino PC5)
* - Referência de tensão: AVCC (5V)
* - Modo: Conversão contínua (Free Running Mode)
* - Interrupção: Ativada (resultado armazenado automaticamente)
* - Prescaler: 128 (para frequência adequada do ADC)
*
* Esta função também desativa o buffer digital no pino de entrada para economia de energia.
*/
void setupHeatingCoolingSystem(void);

/**
 * @brief Define o duty cycle (0–100%) do aquecedor.
 *
 * Controla a saída PWM no pino PD6 (OC0A).
 *
 * @param heaterDutyCycle Valor percentual de 0 a 100.
 */
void setHeaterDutyCycle(uint8_t heaterDutyCycle);

/**
 * @brief Define o duty cycle (0–100%) do resfriador.
 *
 * Controla a saída PWM no pino PD5 (OC0B).
 *
 * @param coolerDutyCycle Valor percentual de 0 a 100.
 */
void setCoolerDutyCycle(uint8_t coolerDutyCycle);

/**
 * @brief Retorna o valor bruto da última leitura do sensor de temperatura.
 *
 * O valor retornado é o resultado da conversão analógica-digital (ADC), com resolução de 10 bits (0–1023),
 * proporcional à tensão de entrada no pino PC5 (canal ADC5).
 *
 * @return uint16_t Valor atual do ADC (nível analógico do sensor)
 */
uint16_t getTemperatureSensorLevel(void);

/**
 * @brief Converte o valor do ADC em temperatura em graus Celsius.
 *
 * A conversão é baseada na equação:
 *    Temperatura (°C) = (ADC - 120) / 8
 *
 * Esta fórmula foi ajustada empiricamente para sensores como o LM35,
 * assumindo alimentação de 5V (AVCC) e resposta linear de 10 mV/°C.
 *
 * @return uint16_t Temperatura aproximada em graus Celsius
 */
uint16_t getTemperatureDegrees(void);

/**
 * @brief Retorna o valor atual da velocidade de rotação em RPM.
 * 
 * A velocidade é calculada a partir do tempo entre bordas sucessivas de um 
 * sinal de entrada conectado ao pino ICP1 (PB0). Assumem-se 7 pulsos por rotação.
 * 
 * @return uint32_t Velocidade em rotações por minuto (RPM).
 */
uint32_t getTachometerVelValue(void);

#endif // HEATING_COOLING_SYSTEM_H

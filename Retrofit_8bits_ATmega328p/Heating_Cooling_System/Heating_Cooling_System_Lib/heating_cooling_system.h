#ifndef HEATING_COOLING_SYSTEM_H
#define HEATING_COOLING_SYSTEM_H

#include <avr/io.h>

/**
 * @brief Configura os pinos e timers para controle PWM do aquecedor e resfriador.
 *
 * - Configura PB1 (OC1A) e PB2 (OC1B) como sa�da.
 * - Ativa PWM r�pido no Timer1.
 * - Define OC1A e OC1B em modo n�o-invertido.
 * - Sem prescaler (frequ�ncia base = 16MHz).
 */
void setupHeatingCoolingSystem(void);

/**
 * @brief Define o duty cycle do aquecedor.
 *
 * @param heaterDutyCycle Valor do duty cycle em percentual (0 a 100).
 */
void setHeaterDutyCycle(uint8_t heaterDutyCycle);

/**
 * @brief Define o duty cycle do resfriador.
 *
 * @param coolerDutyCycle Valor do duty cycle em percentual (0 a 100).
 */
void setCoolerDutyCycle(uint8_t coolerDutyCycle);

#endif // HEATING_COOLING_SYSTEM_H

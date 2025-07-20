#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

/**
 * setupTemperatureSensor
 * 
 * Inicializa o ADC para leitura contínua no canal ADC5 (PC5),
 * configura os registradores do ADC e ativa a interrupção.
 */
void setupTemperatureSensor(void);

/**
 * readTemperatureSensorLevel
 * 
 * Retorna o valor bruto da última conversão ADC (0–1023).
 * Esse valor representa a tensão analógica do sensor convertida pelo ADC.
 *
 * @return uint16_t Valor ADC atual (resolução de 10 bits)
 */
uint16_t readTemperatureSensorLevel(void);

/**
 * readTemperatureDegrees
 * 
 * Converte o valor ADC para graus Celsius com base na equação:
 *    Temperatura (°C) = (ADC - 120) / 8
 * 
 * Esta fórmula está ajustada para um sensor LM35 com Vref = 5V,
 * considerando deslocamento aproximado para compensar a faixa do sensor.
 *
 * @return uint16_t Temperatura em graus Celsius
 */
uint16_t readTemperatureDegrees(void);

#endif // TEMPERATURE_SENSOR_H

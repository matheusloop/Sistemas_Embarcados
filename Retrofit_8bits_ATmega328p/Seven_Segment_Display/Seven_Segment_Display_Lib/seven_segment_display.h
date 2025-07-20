#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#include <stdint.h>

/**
 * @brief Configura os pinos necessários para o display de 7 segmentos.
 * 
 * PORTD (PD0–PD6) será usado para os segmentos (a–g),
 * e PORTB (PB0–PB3) para seleção dos dígitos.
 */
void setupSevenSegmentDisplay(void);

/**
 * @brief Mostra um valor (0–F) em um display específico.
 * 
 * @param value Valor hexadecimal a ser exibido (0x0 a 0xF).
 * @param displayAddress Endereço do display (0 a 3) correspondente a PB0–PB3.
 */
void showSevenSegmentDisplayValue(uint8_t value, uint8_t displayAddress);

/**
 * @brief Limpa a seleção de displays, desligando todos os dígitos.
 */
void cleanSevenSegmentDisplay(void);

/**
 * @brief Inicializa o modo multiplexado e ativa a interrupção do Timer0.
 * 
 * Essa função ativa a exibição cíclica dos 4 displays via interrupção.
 */
void showAllSevenSegmentDisplay(void);

/**
 * @brief Define os valores que serão exibidos em cada um dos 4 displays.
 * 
 * @param valueDisp_0 Valor para o display 0.
 * @param valueDisp_1 Valor para o display 1.
 * @param valueDisp_2 Valor para o display 2.
 * @param valueDisp_3 Valor para o display 3.
 */
void setAllSevenSegmentDisplayValues(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3);

#endif // SEVEN_SEGMENT_DISPLAY_H

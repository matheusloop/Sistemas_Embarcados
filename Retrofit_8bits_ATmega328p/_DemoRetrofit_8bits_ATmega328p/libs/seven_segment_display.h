#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

/**
 * @brief Configura os pinos necessários para o controle do display de 7 segmentos.
 *
 * Segmentos:
 *   - PORTB (PB1–PB4): segmentos A, B, C e D
 *   - PORTD (PD2–PD4): segmentos E, F e G
 * Habilitação dos displays:
 *   - PORTC (PC0–PC3): seleção dos 4 dígitos (displays)
 */
void setupSevenSegmentDisplay(void);

/**
 * @brief Ativa os segmentos de acordo com o código binário fornecido.
 *
 * Cada bit do parâmetro representa um segmento (bit 6 = A, bit 5 = B, ..., bit 0 = G).
 * 
 * @param segmentCode Código binário com os bits correspondentes aos segmentos a serem acesos.
 */
void activeSegments(uint8_t segmentCode);

/**
 * @brief Exibe um valor hexadecimal (0–F) em um display específico.
 *
 * @param value Valor a ser exibido (0x0 a 0xF).
 * @param displayAddress Índice do display (0 a 3) a ser habilitado.
 */
void showSevenSegmentDisplayValue(uint8_t value, uint8_t displayAddress);

/**
 * @brief Desativa todos os segmentos e todos os displays.
 *
 * Útil para evitar sobreposição de informações durante multiplexação.
 */
void cleanSevenSegmentDisplay(void);

/**
 * @brief Ativa o modo multiplexado para os 4 displays usando o Timer2.
 *
 * Configura o Timer2 para gerar interrupções periódicas que atualizam os displays
 * de forma sequencial (multiplexação).
 */
void showAllSevenSegmentDisplay(void);

/**
 * @brief Define os valores individuais a serem mostrados em cada um dos 4 displays.
 *
 * @param valueDisp_0 Valor do display 0.
 * @param valueDisp_1 Valor do display 1.
 * @param valueDisp_2 Valor do display 2.
 * @param valueDisp_3 Valor do display 3.
 */
void setAllSevenSegmentDisplayValues(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3);

#endif // SEVEN_SEGMENT_DISPLAY_H

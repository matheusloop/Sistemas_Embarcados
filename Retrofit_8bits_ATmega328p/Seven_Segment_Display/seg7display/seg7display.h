#ifndef SEG7DISPLAY_H
#define SEG7DISPLAY_H

#include <avr/io.h>
#include <stdint.h>

/*
 * Função: setupSeg7Display
 * ------------------------
 * Configura os pinos necessários para o controle do display de 7 segmentos.
 *
 * PORTC: pinos para os segmentos (a–g).
 * PORTB[3:0]: seleção dos dígitos ativos (multiplexação).
 */
void setupSeg7Display();

/*
 * Função: changeSeg7DisplayValue
 * ------------------------------
 * Define os segmentos do display de 7 segmentos para exibir um valor decimal (0 a 9).
 *
 * value: dígito decimal (0 a 9) a ser exibido.
 *
 * A função utiliza uma tabela de conversão (LUT) com os padrões de segmentos para cada número.
 * O valor é enviado para os pinos da PORTC.
 */
void changeSeg7DisplayValue(uint8_t value);

/*
 * Função: enableSeg7Display
 * -------------------------
 * Ativa um dos dígitos do display de 7 segmentos multiplexado.
 *
 * displayAdress: índice do dígito (0 a 3) a ser ativado.
 *
 * A função limpa os bits PB0-PB3 e ativa apenas o bit correspondente ao dígito desejado.
 */
void enableSeg7Display(uint8_t displayAdress);

/*
 * Função: cleanSeg7Display
 * ----------------------
 * Apaga todos os displays de sete segmentos da placa
 * A função limpa os bits PB0-PB3
 */
void cleanSeg7Display();

/*
 * Função: runSeg7Display
 * ----------------------
 * Atualiza os quatro dígitos do display de 7 segmentos com os valores fornecidos.
 *
 * valueDisp_0 a valueDisp_3: valores decimais a serem exibidos nos dígitos 0 a 3.
 *
 * A função faz a varredura sequencial dos dígitos, típica de displays multiplexados.
 */
void runSeg7Display(uint8_t valueDisp_0, uint8_t valueDisp_1, uint8_t valueDisp_2, uint8_t valueDisp_3);

#endif

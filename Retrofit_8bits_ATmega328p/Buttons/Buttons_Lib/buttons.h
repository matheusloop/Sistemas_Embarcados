/**
 * @file buttons.h
 * @brief Biblioteca para gerenciamento de botões com interrupções (AVR)
 * 
 * Permite o registro de callbacks associados a cada botão (PB4–PB7),
 * usando interrupções baseadas em pinos (PCINT).
 * 
 * @author Matheus
 * @date 28/06/2025
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdint.h>

/**
 * @brief Enumeração para os pinos dos botões.
 */
typedef enum {
    BUTTON_A = 4,  ///< Botão conectado ao pino PB4
    BUTTON_B = 5,  ///< Botão conectado ao pino PB5
    BUTTON_C = 6,  ///< Botão conectado ao pino PB6
    BUTTON_D = 7   ///< Botão conectado ao pino PB7
} ButtonPin;

/**
 * @brief Tipo de função callback para eventos de botão.
 * 
 * @param arg Ponteiro genérico para argumento passado no registro.
 */
typedef void (*button_callback_t)(void* arg);

/**
 * @brief Configura os botões (PB4–PB7) com resistores pull-up e ativa interrupções.
 */
void setupButtons(void);

/**
 * @brief Registra uma função de callback para um botão específico.
 * 
 * @param button Botão ao qual associar o callback (BUTTON_A a BUTTON_D)
 * @param callback Função a ser chamada quando o botão for pressionado
 * @param arg Ponteiro para argumento da função callback
 */
void register_button_callback(ButtonPin button, button_callback_t callback, void* arg);

#endif /* BUTTONS_H_ */

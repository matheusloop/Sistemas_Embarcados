/**
 * @file buttons.c
 * @brief Implementação da biblioteca de botões com interrupções
 */

#include "buttons.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Estrutura interna para armazenar callbacks registrados
typedef struct {
    button_callback_t callback;
    void* arg;
} button_handler_t;

// Vetor de handlers para os botões PB4–PB7
static volatile button_handler_t button_handlers[4] = {0};

void setupButtons(void) {
    // Configura PB4–PB7 como entrada
    DDRB &= 0x0F;

    // Ativa pull-ups nos pinos PB4–PB7
    PORTB |= 0xF0;

    // Habilita interrupção de pino para PCINT0 (PB0–PB7)
    PCICR |= (1 << PCIE0);
    PCMSK0 |= 0xF0;  // Máscara para PB4–PB7

    sei();  // Habilita interrupções globais
}

void register_button_callback(ButtonPin button, button_callback_t callback, void* arg) {
    if (button >= BUTTON_A && button <= BUTTON_D) {
        button_handlers[button - 4].callback = callback;
        button_handlers[button - 4].arg = arg;
    }
}

// Interrupção do grupo PCINT0 (PB0–PB7)
ISR(PCINT0_vect) {
    for (uint8_t i = 0; i < 4; i++) {
        uint8_t pin = i + 4;
        if (!(PINB & (1 << pin)) && button_handlers[i].callback) {
            button_handlers[i].callback(button_handlers[i].arg);
        }
    }
}

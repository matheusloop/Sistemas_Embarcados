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
    // Configura PC0–PC3 como entrada
    DDRC &= 0x0F;

    // Ativa pull-ups nos pinos PC0–PC3
    PORTC |= 0xF0;

    // Habilita interrupção de pino para PCINT0 (PC0–PC3)
    PCICR |= (1 << PCIE1);
    PCMSK1 |= 0x0F;  // Máscara para PC0–PC3

    sei();  // Habilita interrupções globais
}

void register_button_callback(ButtonPin button, button_callback_t callback, void* arg) {
    if (button >= BUTTON_A && button <= BUTTON_D) {
        button_handlers[button].callback = callback;
        button_handlers[button].arg = arg;
    }
}

// Interrupção do grupo PCINT0 (PC0–PC3)
ISR(PCINT1_vect) {
    for (uint8_t pin = 0; pin < 4; pin++) {
        if (!(PINC & (1 << pin)) && button_handlers[pin].callback) {
            button_handlers[pin].callback(button_handlers[pin].arg);
        }
    }
}

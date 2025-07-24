#include <avr/io.h>

#include "heating_cooling_system.h"

void setupHeatingCoolingSystem(void){
   
    DDRD |= ((1 << 5) | (1 << 6));  // Configura os pinos PD5 (OC0B) e PD6 (OC0A) como saída

    // Configura Timer1 para modo PWM rápido
    // COM1A1:0 = 10 (não-invertido para OC0A)
    // COM1B1:0 = 10 (não-invertido para OC0B)
    // WGM11:0 = 11 (modo 14 - Fast PWM com 0xFF como TOP)
    TCCR0A = 0b10100011;

    // WGM13:2 = 10 (com os bits anteriores, forma modo 14)
    // CS10 = 1 (sem prescaler, clk/1)
    TCCR0B = 0b00000011; //T = (256 * 64)/16MHz = ~1 ms 

    // Duty cycle inicial de 0% para ambos os canais
    OCR0A = 0; // Aquecedor
    OCR0B = 0; // Resfriador
}

void setHeaterDutyCycle(uint8_t heaterDutyCycle){
    // Ajusta OCR1A proporcionalmente ao valor percentual
    OCR0A = (255 / 100) * heaterDutyCycle;
}

void setCoolerDutyCycle(uint8_t coolerDutyCycle){
    // Ajusta OCR1B proporcionalmente ao valor percentual
    OCR0B = (255 / 100) * coolerDutyCycle;
}

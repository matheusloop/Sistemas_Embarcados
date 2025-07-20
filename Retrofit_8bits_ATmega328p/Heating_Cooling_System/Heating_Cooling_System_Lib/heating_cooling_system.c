#include <avr/io.h>

void setupHeatingCoolingSystem(void){
   
    DDRB |= ((1 << 1) | (1 << 2));  // Configura os pinos PB1 (OC1A) e PB2 (OC1B) como saída

    // Configura Timer1 para modo PWM rápido
    // COM1A1:0 = 10 (não-invertido para OC1A)
    // COM1B1:0 = 10 (não-invertido para OC1B)
    // WGM11:0 = 11 (modo 14 - Fast PWM com 0xFF como TOP)
    TCCR1A = 0b10100011;

    // WGM13:2 = 10 (com os bits anteriores, forma modo 14)
    // CS10 = 1 (sem prescaler, clk/1)
    TCCR1B = 0b00000001;

    // Duty cycle inicial de 0% para ambos os canais
    OCR1A = 0; // Aquecedor
    OCR1B = 0; // Resfriador
}

void setHeaterDutyCycle(uint8_t heaterDutyCycle){
    // Ajusta OCR1A proporcionalmente ao valor percentual
    OCR1A = (1023 / 100) * heaterDutyCycle;
}

void setCoolerDutyCycle(uint8_t coolerDutyCycle){
    // Ajusta OCR1B proporcionalmente ao valor percentual
    OCR1B = (1023 / 100) * coolerDutyCycle;
}

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "../Seven_Segment_Display_Lib/seven_segment_display.h"

// ========================
// FUNÇÃO PRINCIPAL
// ========================

int main(void){
	uint16_t num0 = 0, num1 = 0;
	setupSevenSegmentDisplay();  // Inicializa os pinos do display de 7 segmentos
	showAllSevenSegmentDisplay();
	
	while(1){
		/**/
		setAllSevenSegmentDisplayValues((num1)%10, (num1+1)%10, (num1+2)%10, (num1+3)%10);
		_delay_ms(20);
		num0++;
		num1 = (num0/100)%10;
		
		
		//showAllSevenSegmentDisplay(0xC, 0xA, 0xF, 0xE);

	}
	return 0;
}

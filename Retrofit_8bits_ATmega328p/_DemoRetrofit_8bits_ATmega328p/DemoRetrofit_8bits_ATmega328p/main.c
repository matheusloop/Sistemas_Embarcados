#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "../libs/seven_segment_display.h"
#include "../libs/heating_cooling_system.h"
#include "../libs/UART_Lib.h"

int main(void){
	uint16_t velResf = 0, temp = 0;
	setupUART();
	
	setupSevenSegmentDisplay();
	showAllSevenSegmentDisplay();
	
	setupHeatingCoolingSystem();
	setCoolerDutyCycle(50);
	
    while (1) {
		velResf = getTachometerVelValue();
		temp = getTemperatureDegrees();

		setAllSevenSegmentDisplayValues((temp/10)%10, temp%10, 0xFF, 0xC);
		
		if(temp <= 40 ){setHeaterDutyCycle(50); setCoolerDutyCycle(0); }
		if(temp >= 70 ){setHeaterDutyCycle(0);  setCoolerDutyCycle(50);}
		
		transmitUART_16bits('V'<<8 |'e'); transmitUART_16bits('l'<<8 |':'); transmitUART_8bits(' ');
		sendASCIIFromInt(velResf); 
		transmitUART_16bits('r'<<8 |'p'); transmitUART_16bits('m'<<8 |'\n');
		
		_delay_ms(500);
    }
}


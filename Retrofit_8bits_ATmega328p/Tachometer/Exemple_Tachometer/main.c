#define F_CPU 16000000UL
#include "../../Heating_Cooling_System/Heating_Cooling_System_Lib/heating_cooling_system.h"
#include "../../Temperature_Sensor/UART_Lib/UART_Lib.h"
#include "../Tachometer_Lib/tachometer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){
	
	setupUART(MYUBRR);
	setupHeatingCoolingSystem();
	setupTachometer();
	setupTachometer();
	
	setCoolerDutyCycle(20);
	
	while (1){
		sendASCIIFromInt(getTachometerVelValue());
		_delay_ms(1000);
	}
}
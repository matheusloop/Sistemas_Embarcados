#include "../../Temperature_Sensor/UART_Lib/UART_Lib.h"
#include "../../Temperature_Sensor/Temperature_Sensor_Lib/temperature_sensor.h"
#include "../Heating_Cooling_System_Lib/heating_cooling_system.h"

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	//uint8_t dt = 0, flag = 1;
	uint8_t temp = 0;
	
	setupHeatingCoolingSystem();
	setupTemperatureSensor();
	setupUART(MYUBRR);
	
	while (1) {
		temp = readTemperatureDegrees();
		sendASCIIFromInt(temp);
		if(temp >= 70) {setHeaterDutyCycle(0); setCoolerDutyCycle(50);}
		if(temp <= 40) {setCoolerDutyCycle(0); setHeaterDutyCycle(50);}
		_delay_ms(500);

	}
}


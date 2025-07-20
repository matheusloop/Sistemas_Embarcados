#define F_CPU 16000000UL 
#include "../UART_Lib/UART_lib.h"
#include "../Temperature_Sensor_Lib/temperature_sensor.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void){
	
	DDRD |= (1<<0);
	PORTD |= (1<<0);
	
	setupUART(MYUBRR);
	setupTemperatureSensor();


	while(1){
		PORTD ^= (1<<0);
		sendASCIIFromInt(readTemperatureDegrees());
		_delay_ms(100);
	}
	
	return 0;
}
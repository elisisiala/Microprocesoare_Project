#include "Adc.h"
#include "Uart.h"
#include "Gpio.h"
#include "Pit.h"
#include "Pwm.h"
int main() {


	UART0_Init(19200);
	
	RGBLed_Init();
	initPWM();
	ADC0_Init();
	initPIT();
	
	long int i;
	for(;;) {	
	
	}
	
}

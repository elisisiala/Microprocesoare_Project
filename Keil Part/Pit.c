#include "Pit.h"
#include "Uart.h"
#include "Adc.h"
#include "Gpio.h"

void initPIT(void)
{
	// Activarea semnalului de ceas pentru perifericul PIT
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	// Utilizarea semnalului de ceas pentru tabloul de timere
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	// Oprirea decrementarii valorilor numaratoarelor in modul debug
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	// Set the value for a period of 1292ms on channel 0
	PIT->CHANNEL[0].LDVAL = 0xD4A2FB;  //canal 0 1292 ms

	// Activate the interrupt on channel 0
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

	// Activate the timer on channel 0
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	//NVIC_ClearPendingIRQ(PIT_IRQn);
	//NVIC_SetPriority(PIT_IRQn,5);
	NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void) {
	
	if(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		//UTILS_PrintTimer(timer_value);
		
		// Declansez o intrerupere ADC
    ADC0->SC1[0] = ADC_SC1_ADCH(11) | ADC_SC1_AIEN_MASK;
		Switch_Led();
		//ADC0_IRQHandler();
		//timer_value++;
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		
	}

}

#include "Pwm.h"

#define SERVO_PIN (1) // PORT A , PIN 1
#define PWM_PERIOD 5000  // PWM period in microseconds (20 ms)
#define PWM_MIN_PULSE 600 // Minimum pulse width for 0 degrees in microseconds
#define PWM_MAX_PULSE 2400 // Maximum pulse width for 180 degrees in microseconds


void initPWM(){
	
	
	// Activarea semnalului de ceas pentru utilizarea LED-ului de culoare rosie
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	// Utilizarea alternativei de functionare pentru perifericul TMP
	// TMP2_CH0
	PORTA->PCR[SERVO_PIN] |= PORT_PCR_MUX(3);
	
	// Selects the clock source for the TPM counter clock (MCGFLLCLK) - PG. 196
	// MCGFLLCLK Freq. - 48 MHz
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	// Activarea semnalului de ceas pentru modulul TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM2(1);
	
	// Divizor de frecventa pentru ceasul de intrare
	// PWM CLK -> 48MHz / 128 = 48.000.000 / 128 [Hz] = 375.000 [Hz] = 375 kHz
	TPM2->SC |= TPM_SC_PS(7);
	
		// LPTPM counter operates in up counting mode. - PG. 553
	// Selects edge aligned PWM
	TPM2->SC |= TPM_SC_CPWMS(0); 
	
	// LPTPM counter increments on every LPTPM counter clock
	TPM2->SC |= TPM_SC_CMOD(1); //lucrez in LPTPM mode 
	
	// Set TPM0 period
  TPM2->MOD = PWM_PERIOD - 1;
    
    // Set TPM0_CH0 pulse width for starting position (0 degrees)
 // TPM2->CONTROLS[0].CnV = 1000;  // Adjust this value for the starting position
    
    // Set TPM0_CH0 to PWM High-true pulses
  TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; 
    
    // Enable TPM0 module
  TPM2->SC |= TPM_SC_CMOD(1);

	
}

void rotate(int angle){
    //int pulseWidth = 1000+ (angle * (PWM_PERIOD - 1)) / 360;
    
    // Update TPM0_CH0 pulse width
		//uint16_t pulseWidth = PWM_MIN_PULSE + (uint16_t)((PWM_MAX_PULSE - PWM_MIN_PULSE) * angle / 180);
		// sa mentin pulsatia intre minim si maxim

		//300 directia ceasului
		//250 sta
		//200 directia anti ceas
	
		//TPM2->CONTROLS[0].CnV = (375 * 10 * angle) / 100;
	
    TPM2->CONTROLS[0].CnV = (uint32_t)angle; //bag valoarea care trebuie transmisa (pe care o s-o primeasca servo motorul)
		//delay_ms(1000);

}
#include "Gpio.h"

//#define LED_PIN (12) // PORT A
#define RED_LED_PIN (18) // PORT B , PIN 18
#define GREEN_LED_PIN (19) // PORT B
#define BLUE_LED_PIN (1) // PORT D


void RGBLed_Init(void){
	
	// Activarea semnalului de ceas pentru pinii folositi ?n cadrul led-ului RGB
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	
		// --- GREEN LED ---
	
	// Utilizare GPIO ca varianta de multiplexare
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
	
	// Configurare pin pe post de output
	GPIOB_PDDR |= (1<<GREEN_LED_PIN);
	
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOB_PSOR |= (1<<GREEN_LED_PIN);
	
	// --- RED LED ---
	
	// Utilizare GPIO ca varianta de multiplexare
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
	
	// Configurare pin pe post de output
	GPIOB_PDDR |= (1<<RED_LED_PIN);
	
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOB_PSOR |= (1<<RED_LED_PIN);
	

	
	// --- BLUE LED ---
	
		// Utilizare GPIO ca varianta de multiplexare
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);
	
	// Configurare pin pe post de output
	GPIOD_PDDR |= (1<<BLUE_LED_PIN);
	
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOD_PSOR |= (1<<BLUE_LED_PIN);
	
	
}

int led_st=0;
void Switch_Led(void)
{
	 
	led_st+=1;
	led_st%=4;
	switch(led_st)
	{
		case 0:
			GPIOD_PCOR |= (1<<BLUE_LED_PIN); //white
			GPIOB_PCOR |= (1<<GREEN_LED_PIN);
			GPIOB_PCOR |= (1<<RED_LED_PIN);
			break;
		case 1:
			GPIOD_PCOR |= (1<<BLUE_LED_PIN); //cyan
			GPIOB_PCOR |= (1<<GREEN_LED_PIN);
			GPIOB_PSOR |= (1<<RED_LED_PIN);
			break;
		case 2:
			GPIOD_PSOR |= (1<<BLUE_LED_PIN);	//yellow
			GPIOB_PCOR |= (1<<GREEN_LED_PIN);
			GPIOB_PCOR |= (1<<RED_LED_PIN);
			break;
		case 3: 
			GPIOD_PSOR |= (1<<BLUE_LED_PIN); //black
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			GPIOB_PSOR |= (1<<RED_LED_PIN);
			break;
	}
}


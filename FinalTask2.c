////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Lab Task:
//
// Set up three LEDs which will have their brightness controlled by a potentiometer. Hook a button up to EXT_INT0 which will cycle the currently
// selected LED.
//
// Circuit setup:  Button for triggering EXT_INT0,
//				   Potentiometer connected to ADC0,
//				   3 LEDs, connected to analog outputs pins. Do not forget resistors!
//
// Requirements:   1. 3 LEDs will switch on one after the other and the direction will depend on the value from the potentiometer.
//
//				   2. The button connected to EXT_INT0 will change the brightness such that it goes from dim to bright and then from bright to dim
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <avr/io.h>
#include "avr/interrupt.h"
#define F_CPU 16000000UL
#include "util/delay.h"

int main(void)
{
	ADCSRA = 0b10000111;  //Enable ADC, set prescaler
	ADCSRB = 0b01000000;  // Enable free running mode option
	ADMUX  = 0b00000000;  // Set ADC0 as input
	
	DDRC   = 0b00000000;  //set portC as input 
	DDRD   = 0b11111111;  //set portD as output
	
	//interrupt button set-up
	EIMSK = 0b000000001;  
	EICRA = 0b000000011;
	
	sei(); //enabling global interrupts
	
	while(1)
	{
		ADCSRA |= 1 << ADSC;
		if(ADC > 512)
		{
			PORTD = 0b00100000;
			_delay_ms(500);
			PORTD = 0b01000000;
			_delay_ms(500);
			PORTD = 0b10000000;
			_delay_ms(500);
		} else
		{
			PORTD = 0b10000000;
			_delay_ms(500);
			PORTD = 0b01000000;
			_delay_ms(500);
			PORTD = 0b00100000;
			_delay_ms(500);
		}
	}
}

ISR(INT0_vect)
{
	TIMSK1 = 0b00000011; // OCIE1A enabled (compare register A)
	TCCR1A = 0b00000000; // Fast PWM, clear on HIGH, set on BOTTOM
	TCCR1B = 0b00000000; // set waveform gen mode and prescaler
	OCR1A  = 0x0000;	 // Change this value to change the LED brightness

	//changing the brightness from dim to bright and then bright to dim
	int i;
	for(i = 0; i <= 1023; i++)
	{
		OCR1A = i*64;
		_delay_ms(1);
	}
	for(i = 1023; i >= 0; i--)
	{
		OCR1A = i*64;
		_delay_ms(1);
	}
	
	TIMSK1 = 0b00000000; //disabling TimerCompare registers
}

ISR(TIMER1_COMPA_vect)
{
	PORTD = 0x00; //switching off LEDs
}

ISR(TIMER1_OVF_vect)
{
	PORTD = 0xFF; //swithcing on LEDs
}
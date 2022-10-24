//Lab 3 from Embedded Systems 

/*
    LAB TASKS   

The task was to write a C progam to make the brightness 
of the LED gradually increase.  

*/


#include <avr/io.h> 
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

int main (void){ 
    //sets OC1A and OC1B on Compare match and the mode to PWM mode 
    //clearing OC1A and OC1B on Compare match
    TCCR1A |= (1<<COM1A1) | (1<<WGM11) ;

    //setting prescaler to 1 and sets the mode to CTC mode 
    TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10); 

    //in CTC mode the counter resets when the it matches either ICR1 or OCR1A
    ICR1 = 0xFF; 
    OCR1A = 0xe; 

    //setting OC1A to output 
    DDRB |= (1<<PORTB1); 

    //gradually increasing the brightness
    while (1){
        _delay_ms(5); 
        //incrementing OCR1A 
        OCR1A = OCR1A + 0xFF; 
    }
}


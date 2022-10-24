//Lab 3 from Embedded Systems 

/*
    LAB TASKS   

The task was to write a C progam to make LEDs blink using a Timer overflow interrupt. 

*/

#include <avr/io.h> 
#define F_CPU 16000000UL //setting CPU clock
#include <util/delay.h> 
#include <avr/interrupt.h> 

int main (){ 
    //setting portD to output
    DDRD = 0XFF; 
    //enabling timer1 overflow
    TIMSK1 = 0b00000001; 
    //setting a compare value equivalent to 1 second
    TCNT1 = 63974; //i think this is supposed to be OCR1A
    //setting prescaler to 256 
    TCCR1B = (1<<CS12); 
    //enabling global interrupts 
    sei(); 

    while(1){

    }
}

//timer overflow function
ISR(TIMER1_OVF_vect){
    //toggling portD on or off 
    PORTD ^= 0xFF; 
}

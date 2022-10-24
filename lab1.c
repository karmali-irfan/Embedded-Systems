//Lab 1 from Embedded Systems 

/*
    LAB TASKS   

The task was to write a C progam to make 3 LEDs blink one half a second after the other.
Triggering an external interrupt would make the 3 LEds blink together 3 times simultaneously.

*/


#include <avr/io.h>
#define F_CPU 16000000UL //Define cpu clock as 16MHz 
#include <util/delay.h>
#include <avr/interrupt.h> 



//Interrupt code, that will be executed if an external interrupt is triggered
ISR (INT0_vect){ 
    //All three leds will blink 3 times simultaneously 
    DDRB = 0xFF; 
    _delay_ms(500);
    DDRB = 0xFF; 
    _delay_ms(500);
    DDRB = 0xFF; 
    _delay_ms(500);
}

int main (void){
    //setting portD as an input
    DDRD = 0x00; 
    //defining the interrrupt (any logical change will trigger an interrupt)
    EICRA = (0<<ISC01) | (1<<ISC00);
    //the interrupt was connected at INT0 
    EIMSK = (1<<INT0); 
    //enabling global interrupts
    sei(); 

    while(1){
        //the three LEDs connected in parallel will blink one after the other
        DDRB = (1<<PB0);
        _delay_ms(500);
        DDRB = (1<<PB1); 
        _delay_ms(500);
        DDRB = (1<<PB2); 
        _delay_ms(500); 
    }
}
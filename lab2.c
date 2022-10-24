//Lab 2 from Embedded Systems 

/*
    LAB TASKS   

The task was to write a C progam to control the brightness of the LED
using clock cycles and PWM/CTC modes. 

*/


#include <avr/io.h>
#define F_CPU 16000000UL //Define cpu clock as 16MHz 
#include <util/delay.h>
#include <avr/interrupt.h> 

void init_timer(){
    //enabling TimerCompareMAtchA 
    TIMSK |= (1<<OCIE1A); 
    //using CTC mode and setting prescaler to 256
    TCCR1B |= (1<<WGM12) | (0<<CS11) | (0<<CS10) | (1<<CS12); 
    //initializing 16 bittimer counter 
    TCNT1 = 0;
    //setting compare value 
    OCR1A = 65000;
    //enabling global interrupts
    sei(); 
}

//Timer interrupt function
ISR(TIMER1_COMPA_vect){
    
    //When PortD is high TCNT1 will count to 300 and then set the output to zero.
    if(PORTD == 0xFF){
        OCR1A = 300; 
    }
    //When PortD is low TCNT1 will count to 12000 and then set the output to 1
    else {
        OCR1A = 12000; 
    }
    //toggling portD
    PORTD ^= 0xFF; //i think is supposed to be 0xFF
}

int main (){
    //setting portD as output
    DDRD |= 0XFF; 
    init_timer(); //function call 
    while (1){
    }
}
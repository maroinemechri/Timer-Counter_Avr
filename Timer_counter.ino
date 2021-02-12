//timer interrupts
//by Marwene Mechri
//June 2012
//https://marwene.mechri@gmail.com

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

//timer setup for timer0, timer1, and timer2.
//For arduino uno or any board with ATMEL 328/168.. diecimila, duemilanove, lilypad, nano, mini...
//this code will enable all three arduino timer interrupts.
//timer0  doesn't allow to control this register from the arduino ide . used bu the millis()
//timer1 
//timer2  as Timer0 .
//https://exploreembedded.com/wiki/AVR_Timer_programming
//http://maxembedded.com/2011/06/avr-timers-timer2/#:~:text=Since%20TIMER2%20is%20an%208,don't%20%E2%80%93%20Asynchronous%20Operation.

#include <avr/io.h>
#include <avr/interrupt.h>
void Timer2Delay(void);
void Timer2Init(void);
volatile char cnt=0;
void Timer2DelayOverFlow(void)
{
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR2B |= (1 << CS22) | (1 << CS20)| (1 << CS21);  // page 117 prescale 1024 
  // enable timer overflow interrupt select 
  TIMSK2 |= (1 << TOIE0);
}

void Timer2Init(void)
{
    cli();     //stop interrupts
    TCCR2A = 0;// set entire TCCR1A register to 0
    TCCR2B = 0;// same for TCCR1B
    TCNT2  = 0;//initialize counter value to 0
    sei();     //allow interrupts
    //end setup
}
void Timer2DelayCtc(void)
{
    OCR2A = 100;//The Output Compare Register A contains an 8-bit value that is continuously compared with the counter value (TCNT0).
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);  //PAGE 107
    // Set CS22 and CS20 bits for 1024 prescaler
    TCCR2B |= (1 << CS22) | (1 << CS20)| (1 << CS21);  // page 117 prescale 1024    
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A); 
}

void setup() { 
 /*Initialization*/ 
 Timer2Init();  //timer 0 ans 2 is the same configuration 
 //Timer2Delay_overflow();
 Timer2DelayCtc();
 Serial.begin(9600);  
}

void loop() 
{
  // put your main code here, to run repeatedly:
 // Serial.println("ok");
}
ISR(TIMER2_OVF_vect )   // TIMER0_OVF_vect    this register used by millis()               // Reset and Interrupt Vectors in ATmega48A and ATmega48PA page 66
{
    cnt++;
    if(cnt >= 61)
    {
     Serial.println("ok"); //every second print "ok"
     cnt=0;
     
    }
}

ISR(TIMER2_COMPA_vect)
{
      cnt++;
    if(cnt > 100)
    {
     Serial.println("YES "); //every second print "ok"
     cnt=0;
     
    }
}

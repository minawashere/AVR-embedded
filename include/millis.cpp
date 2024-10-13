#include "millis.h"



volatile unsigned long milliseconds = 0;
volatile unsigned long millis_fraction = 0;

ISR(Timer0_OVF_vect){
  milliseconds += MILLIS_INCREMENT;
  millis_fraction += FR_INCREMENT;

  if(millis_fraction >= FR_MAX){
    milliseconds += millis_fraction / 1000;
    millis_fraction -= FR_MAX;
  }
}

//enable timer0 interrupts
//set timer0 prescaler to 64
void millis_init(void){
  TCCR0A = 0;
  TCCR0B = (1 << CS01) | (1 << CS00);
  TIMSK0 |= (1 << TOIE0);
}

unsigned long millis(void){
  unsigned long m = milliseconds + (int)TCNT0 / 1000;
  return m;
}


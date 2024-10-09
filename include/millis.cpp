#include "millis.h"

#define SYSTEM_CLOCK 16000000
#define PRESCALER 64
#define TIMER0_TICKS 256
#define TIMER0_OVERFLOW ((PRESCALER * TIMER0_TICKS * 1000000) / SYSTEM_CLOCK) //microseconds
#define MILLIS_INCREMENT (TIMER0_OVERFLOW / 1000)
#define FR_INCREMENT (TIMER0_OVERFLOW % 1000)
#define FR_MAX 1000

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


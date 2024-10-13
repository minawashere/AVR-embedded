
#include "frequency.h"

//set interrupt pin0
//using configured timer1 (PWM_write) and prescallr of 64
//using macros from millis.h
//overflow interrupt will be used to handle the number of cycles





volatile int period = 0;
volatile int prev_time = 0; //storing the prev tick number
volatile int cycles = 0;


ISR(INT0_vect) {

}

ISR(TIMER1_OVF_vect) {
    cycles++;
}

void frequency_init(void) {
    PWM_init();

}

float getFrequency() {
}
#pragma once
#include "frequency.h"
#define PRESCSLER1 64

//set interrupt pin0
//using configured timer1 (PWM_write) and prescallr of 64
//using macros from millis.h
//overflow interrupt will be used to handle the number of cycles

volatile int start_tick = 0;
volatile int end_tick = 0;
volatile int prev_cycles = 0;
volatile int cycles = 0;


ISR(INT0_vect) {
  prev_cycles = cycles;
  cycles = 0;
  end_tick = start_tick;
  start_tick = TCNT1;
}

ISR(TIMER1_OVF_vect) {
    cycles++;
}

void frequency_init(void) {
    PWM_init();
    EICRA |= (1 << ISC01) | (1 << ISC00); //set interrupt request on the rising edge of INT0
    EIMSK |= (1 << INT0);
}

float getFrequency() {
    int period = ICR1 * (prev_cycles - start_tick - 1) + end_tick;
    period *= PRESCSLER1 / SYSTEM_CLOCK;
    return 1 / period;
}
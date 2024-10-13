
#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#define SYSTEM_CLOCK 16000000
#define PRESCALER 64
#define TIMER0_TICKS 256
#define TIMER0_OVERFLOW ((PRESCALER * TIMER0_TICKS * 1000000) / SYSTEM_CLOCK) //microseconds
#define MILLIS_INCREMENT (TIMER0_OVERFLOW / 1000)
#define FR_INCREMENT (TIMER0_OVERFLOW % 1000)
#define FR_MAX 1000

void millis_init(void);
unsigned long millis(void);


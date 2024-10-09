
#include "analogWrite.h"
#define map(x, in_min, in_max, out_min, out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

//using timer1
// set mode to fast pwm
// using prescaler 64, top value will be assigned to (4999) to run at 50hz
// f = clock / (prescaler * ( 1 + TOP))
// noninverting mode, set high on bottom, clear on OCM,
// edge cases: 255, writes pin high, 0, writes pin low, return


void PWM_write(int dutyCycle) {
    DDRB |= (1<<PB1);
    if(dutyCycle == 0) {
        PORTB &= ~(1<<PB1);
        return;
    }
    if(dutyCycle == 100) {
        PORTB |= (1<<PB1);
        return;
    }
    dutyCycle = map(dutyCycle, 0, 100, 0, 4999);
    OCR1A = dutyCycle;
    TCCR1A |= (1<<WGM11); //fast pwm, top = ICR1 (mode 14)
    TCCR1B |= (1<<WGM12) | (1<<WGM13);
    TCCR1A |= (1<<COM1A1);
    TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler = 64
    ICR1 = 4999; // setting top value
}

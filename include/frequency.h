#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <analogWrite.h>
#include <millis.h>



void frequency_init(void);
float getFrequency();
#pragma once
#ifndef _TIMER_US_H_
#define _TIMER_US_H_
#include <stdint.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <avr/io.h>

ISR(TIMER1_COMPA_vect);
uint64_t micros20(void);
void initTimer(void);
#endif
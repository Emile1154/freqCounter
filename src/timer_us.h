#pragma once
#ifndef _TIMER_US_H_
#define _TIMER_US_H_
#include <stdint.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <avr/io.h>

//прерывание таймера по сравнению
ISR(TIMER1_COMPA_vect);

/**
 * @param void
 * @return uint64_t значение таймера 1 ед. = 20 мкс
*/
uint64_t micros20(void);

/**
 * Инициализация таймера
 * @param void
 * @return void
 */
void initTimer(void);

#endif
#pragma once
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <avr/io.h>
#include <pinConfig.h>

/**
 * Зажечь определенное число на выбранном разряде индикатора
 * @param val число записи 0-9.
 * @param digit разряд 0-4.
 * @return void
 */
void writeLED(uint8_t val, uint8_t digit);

#endif
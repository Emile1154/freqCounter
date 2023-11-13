#pragma once
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <avr/io.h>
#include <pinConfig.h>

/**
 * Write a value to a specific digit.
 *
 * @param val The value to write 0-9.
 * @param digit The digit to write the value to 0-4.
 *
 * @throws None.
 */
void writeLED(uint8_t val, uint8_t digit);

#endif
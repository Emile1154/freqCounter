#pragma once
#ifndef _PINCONFIG_H_
#define _PINCONFIG_H_

#define ENA_1 PD0   // 5 разряд индикатора
#define ENA_2 PD1   // 4 разряд индикатора
#define ENA_3 PD2   // 3 разряд индикатора
#define ENA_4 PD4   // 2 разряд индикатора
#define ENA_5 PD5   // 1 разряд индикатора

#define F_VECT PD3  // вход сигнала для подсчета частоты
#define MUX_SEL PD6 // выход управление реле

// сегменты индикатора
#define A PORTC0    
#define B PORTC1
#define C PORTC2
#define D PORTC3
#define E PORTC4
#define F PORTC5
#define G PORTC7

// входы логических сигналов управления реле
#define CA PA0
#define CB PA1
#define CC PA2
#define CD PA3


#endif
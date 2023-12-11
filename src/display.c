#include <display.h>

 /*     
 *  Общий катод
 * 
 *      a
 *     +++
 *   +     + 
 * f +     + b  
 *   +  g  + 
 *     +++ 
 *   +     +
 * e +     + c
 *   +  d  +
 *     +++
 */   
void writeLED(uint8_t val, uint8_t digit){
    switch (val)  // выбор зажигания числа от 0-9 на разряде
    {
        case 0:
            PORTC &= ~(1 << G);

            PORTC |= (1 << A) | (1 << B) | (1 << C) | (1 << D) | (1 << E) | (1 << F);
            break;
        case 1:
            PORTC &= ~(1 << A);
            PORTC &= ~(1 << D); 
            PORTC &= ~(1 << E); 
            PORTC &= ~(1 << F); 
            PORTC &= ~(1 << G);

            PORTC |= (1 << B) | (1 << C);
            break;
        case 2:
            PORTC &= ~(1 << C); 
            PORTC &= ~(1 << F);

            PORTC |= (1 << A) | (1 << B) | (1 << D) | (1 << E) | (1 << G);
            break;
        case 3:
            PORTC &= ~(1 << E);
            PORTC &= ~(1 << F);

            PORTC |= (1 << A) | (1 << B) | (1 << C) | (1 << D) | (1 << G);
            break;
        case 4:
            PORTC &= ~(1 << A); 
            PORTC &= ~(1 << D); 
            PORTC &= ~(1 << E);

            PORTC |= (1 << B) | (1 << C) | (1 << F) | (1 << G);
            break;
        case 5:
            PORTC &= ~(1 << B);
            PORTC &= ~(1 << E);
            
            PORTC |= (1 << A) | (1 << C) | (1 << D) | (1 << F) | (1 << G); 
            break;
        case 6:
            PORTC &= ~(1 << B);

            PORTC |= (1 << A) | (1 << C) | (1 << D) | (1 << E) | (1 << F) | (1 << G);
            break;
        case 7:
            PORTC &= ~(1 << D); 
            PORTC &= ~(1 << E); 
            PORTC &= ~(1 << F);
            PORTC &= ~(1 << G);

            PORTC |= (1 << A) | (1 << B) | (1 << C);
            break;
        case 8:
            PORTC |= (1 << A) | (1 << B) | (1 << C) | (1 << D) | (1 << E) | (1 << F) | (1 << G);
            break;
        case 9:
            PORTC &= ~(1 << E);
            PORTC |= (1 << A) | (1 << B) | (1 << C) | (1 << D) | (1 << F) | (1 << G);
            break;
    }
    switch (digit)  // выбор разряда на индикаторе
    {
        case 0:
            PORTD &= ~(1 << ENA_1); 
            PORTD &= ~(1 << ENA_2); 
            PORTD &= ~(1 << ENA_3); 
            PORTD &= ~(1 << ENA_4);

            PORTD |= (1 << ENA_5);
            break;
        case 1:
            PORTD &= ~(1 << ENA_1); 
            PORTD &= ~(1 << ENA_2); 
            PORTD &= ~(1 << ENA_3); 
            PORTD &= ~(1 << ENA_5);

            PORTD |= (1 << ENA_4);
            break;
        case 2:
            PORTD &= ~(1 << ENA_1);
            PORTD &= ~(1 << ENA_2);
            PORTD &= ~(1 << ENA_4);
            PORTD &= ~(1 << ENA_5);

            PORTD |= (1 << ENA_3);
            break;
        case 3:
            PORTD &= ~(1 << ENA_1);
            PORTD &= ~(1 << ENA_3);
            PORTD &= ~(1 << ENA_4);
            PORTD &= ~(1 << ENA_5);

            PORTD |= (1 << ENA_2);
            break;
        case 4:
            PORTD &= ~(1 << ENA_4);
            PORTD &= ~(1 << ENA_2);
            PORTD &= ~(1 << ENA_3);
            PORTD &= ~(1 << ENA_5);

            PORTD |= (1 << ENA_1);
            break;
    }
}
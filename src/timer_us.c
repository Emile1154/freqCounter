#include <timer_us.h>

volatile uint64_t t_micros = 0;
ISR(TIMER1_COMPA_vect) {
    ++t_micros; // 20 us period
}

void initTimer(void){
  TCCR1A = 0; // Set Timer1 control registers to 0
  TCCR1B = 0;
  TIMSK1 |= (1 << OCIE1A); //enable compare 
  TCNT1 = 0; // Initialize the counter value to 0
  TCCR1B |= (1 << CS10) | (0 << CS11) | (0 << CS12); //div 1
  TCCR1B |= (1 << WGM12) | (0 << WGM13); //CTC mode  
  // in CTC mode freqency_interrupt = F_CPU/(2*div * (OCR1A+1)) OCR1A 16bit value 0-65535 dec 
  // frequency_interrupt = 50kHz
  OCR1A = 79; 
}


uint64_t micros20(void){
  uint64_t result;
  // Ensure this cannot be disrupted
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    result = t_micros;
  }
  return result;
}



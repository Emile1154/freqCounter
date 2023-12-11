#include <timer_us.h>
//счетчик
volatile uint64_t t_micros = 0;

ISR(TIMER1_COMPA_vect) {
    ++t_micros; // увеличиваем счетчик каждые 20 микросекунд
}
void initTimer(void){
  TCCR1A = 0; // Set Timer1 control registers to 0
  TCCR1B = 0;
  TIMSK1 |= (1 << OCIE1A); //таймер по сравнению
  TCNT1 = 0; // инициализируем счетчик
  TCCR1B |= (1 << CS10) | (0 << CS11) | (0 << CS12); //делитель 1
  TCCR1B |= (1 << WGM12) | (0 << WGM13); //режим CTC  
  // в режиме CTC частота расчитывается по формуле:
  // freqency_interrupt = F_CPU/(2*div * (OCR1A+1)) OCR1A 16bit значение 0-65535 
  // где frequency_interrupt = 50kHz
  OCR1A = 79; 
}
uint64_t micros20(void){
  uint64_t result;
  //транзакция
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    result = t_micros;
  }
  return result;
}



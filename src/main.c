#include <timer_us.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <pinConfig.h>
#include <display.h>

volatile uint16_t counter;
ISR(INT1_vect){
  counter++;
}

void initPins(){
  // ena_1 ena_2 ena_3 ena_4 ena_5 pin as output for select digit indicator LED
  DDRD |= (1 << ENA_1) | (1 << ENA_2) | (1 << ENA_3) | (1 << ENA_4) | (1 << ENA_5);
  DDRD |= (1 << MUX_SEL);
  DDRD &= ~(1 << F_VECT); //INT1 pin as input

   //a b c d e f g as output to indicate LEDs
  DDRC |= (1 << A) | (1 << B) | (1 << C) | (1 << D) | (1 << E) | (1 << F) | (1 << G);  

  //ca cb cc cd as input for switch MUX 
  DDRC &= ~(1 << CA) | ~(1 << CB) | ~(1 << CC) | ~(1 << CD);
}


void initINT1(){
  EICRA |= (1 << ISC11) | (0 << ISC10); //falling edge
  EIMSK |= (1 << INT1);  //allow interrupt INT1
}

uint8_t updated = 0;
uint16_t calculateFrequency(){
  static uint64_t timer;
  static uint16_t frequency;
  if(micros20() - timer >= 50000){ // 1 second period 50kHz timer freq
    frequency = counter;
    counter = 0;
    updated = 1;
    timer = micros20();
  }
  return frequency;
}

void checkLogicSignal(){
  static uint64_t timer;
  uint8_t a, b, c, d;
  uint8_t result;
  if(micros20() - timer >= 5000){  //100 ms period 50kHz timer freq
    a = PINA & (1 << CA);
    b = PINA & (1 << CB);
    c = PINA & (1 << CC);
    d = PINA & (1 << CD);
    result = (a * d + c * b) + d * c;
    timer = micros20(); 
  }
  if(result){
    PORTD |= (1 << MUX_SEL);
  }else{
    PORTD &= ~(1 << MUX_SEL);
  }
}

int main(){
  initPins();
  initINT1();
  initTimer();
  sei();  //enable interrupts
  uint16_t frequency;
  uint64_t timer = 0;
  uint8_t digit = 0;
  char nums[5];
  uint8_t char_counter = 0;
  while(1){
    frequency = calculateFrequency();

    //get chars from frequency
    if(updated){
      while(frequency){
        nums[char_counter] = frequency % 10;
        frequency /= 10;
        char_counter++;
      }
      char_counter=0;
      updated = 0;
    }
  
    if(micros20() - timer >= 200){ // 4 ms period 50kHz timer freq
      writeLED(nums[digit], digit);
      digit++;
      if(digit > 4){
        digit = 0;
      }
      timer = micros20();
    }
    checkLogicSignal();
  }  
}
#include <timer_us.h>   //таймер
#include <avr/io.h>     
#include <avr/interrupt.h>
#include <pinConfig.h>  // используемые пины
#include <display.h>    //индикатор

//счетчик импульсов
volatile uint16_t counter;

//прерывание по срезу INT1
ISR(INT1_vect){
  counter++;
}

//инициализация портов
void initPins(){
  // ena_1 ena_2 ena_3 ena_4 ena_5 пины настроенные на выход для выбора разряда индикатора
  DDRD |= (1 << ENA_1) | (1 << ENA_2) | (1 << ENA_3) | (1 << ENA_4) | (1 << ENA_5);
  DDRD |= (1 << MUX_SEL); //настройка пина как выход для управление реле
  DDRD &= ~(1 << F_VECT); //настройка пина как вход для подсчета импульсов 

   //a b c d e f g настроенные на выход для сегментов индикатора
  DDRC |= (1 << A) | (1 << B) | (1 << C) | (1 << D) | (1 << E) | (1 << F) | (1 << G);  

  //ca cb cc cd настроенные на вход для логических сигналов
  DDRC &= ~(1 << CA) | ~(1 << CB) | ~(1 << CC) | ~(1 << CD);
}

//инициализация прерывания INT1 
void initINT1(){
  EICRA |= (1 << ISC11) | (0 << ISC10); // срабатывание INT1 по срезу
  EIMSK |= (1 << INT1);  // включить прерывание INT1
}

//метод расчета частоты
uint16_t calculateFrequency(){
  static uint64_t timer;     //буффер таймера
  static uint16_t frequency; //частота
  if(micros20() - timer >= 50000){ // 1 секунда период измерения, 50кГц частота таймера
    frequency = counter;  //сохраняем частоту
    counter = 0;          //обнуляем счетчик
    timer = micros20();   //обновляем время
  }
  return frequency;   //возвращаем частоту
}


//метод проверки логических сигналов
void checkLogicSignal(){
  static uint64_t timer;
  uint8_t a, b, c, d;
  uint8_t result;
  if(micros20() - timer >= 5000){  //проверка каждые 100 мс, частота таймера 50кГц
    //чтение порта
    a = PINA & (1 << CA);
    b = PINA & (1 << CB);
    c = PINA & (1 << CC);
    d = PINA & (1 << CD);
    //вычисление результата по заданому логическому уравнению
    result = (a * d + c * b) + d * c;
    timer = micros20(); 
  }
  if(result){  // если истина, переключить реле
    PORTD |= (1 << MUX_SEL);
  }else{       // иначе переключить реле в исходное состояние
    PORTD &= ~(1 << MUX_SEL);
  }
}

int main(){
  initPins();  //инициализация портов
  initINT1();  //инициализация прерывания
  initTimer(); //инициализация таймера
  sei();       //включить прерывания
  uint16_t frequency;           //частота
  uint16_t prev_frequency = 0;  //предыдущая частота
  uint64_t timer = 0;           //буффер таймера
  uint64_t hold_timer = 0;      //таймер удержания индикации
  uint8_t digit = 0;            //текущий разряд
  char nums[5];                 //массив чисел для индикаторов
  uint8_t char_counter = 0;     //счётчик символов
  while(1){
    frequency = calculateFrequency();  //получить частоту

    //если изменилось значение частоты и прошло более 7 секунд, то обновить буффер индикатора
    if(prev_frequency != frequency && micros20() - hold_timer >= 350000){ // 1 cекунда = 50 000 
      //получить символы из числа frequency
      while(frequency){
        nums[char_counter] = frequency % 10;  //делим число на 10 и записываем остаток в буффер
        frequency /= 10;                      //делим число на 10
        char_counter++;                       //увеличиваем счётчик
      }
      char_counter = 0;                 //обнуляем счётчик
      hold_timer = micros20();          //обновляем таймер
      prev_frequency = frequency;       //сохраняем предыдущую частоту
    }
  
    if(micros20() - timer >= 200){   //отображать разряд индикатора периодом 4 мс
      writeLED(nums[digit], digit);  //зажечь индикатор с определнным разрядом и числом
      digit++;                       //переключить разряд
      if(digit > 4){                 //если разряд переполнен 
        digit = 0;                   //обнулить разряд
      }
      timer = micros20();            //обновить таймер
    }
    checkLogicSignal();              //проверка логических сигналов
  }  
}
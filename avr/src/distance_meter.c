/*
 * distance_meter.c
 *
 * Created: 7.10.2015 13:45:12
 *  Author: e1100983
 * 
 * 1 tick  125ns = 0.125us
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "include/USART_driver.h"

#define ECHO PD4
#define TRIG (1<<PE6)

#define SCALE 0.125
#define CM    58

static uint16_t tim = 0;
static uint8_t flag = 0;
static uint8_t _ovf = 0;
static uint8_t c_echo = 0; // echo complete
uint8_t meas;

void initINT();
void initTIM();

void trigger()
{
  uint32_t  trig;
  uint8_t   loop;
  PORTE |= TRIG;
  _delay_us(10);
  PORTE &= ~TRIG;
}


ISR(TIMER1_CAPT_vect)
{
  if(!flag)
  {
    TCNT1 = 0;
    TCCR1B &= ~(1 << ICES1);
    flag = 1;
  }
  else
  {
    tim = ICR1;
    c_echo = 1;
    flag = 0;
    TCCR1B |= (1 << ICES1);
  }
}

ISR(TIMER1_OVF_vect)
{
  if(flag)
    _ovf++;
}

int main(void)
{
  DDRD &= ~(1 << ECHO);
  DDRE |= TRIG;
  

  USART_Init();
  initTIM();
  
  sei();
  
  trigger();

  while(1)
  {
    if(c_echo == 1)
    {
      
      USART_Transmit(USART_MODBUS, (tim >> 8));
      USART_Transmit(USART_MODBUS, tim);
      
      meas = (uint8_t)(((double)tim)/CM);
      USART_Transmit(USART_MODBUS, 0xFF);

      USART_Transmit(USART_MODBUS, (meas));
      
      _delay_ms(3000);
      c_echo = 0;
      //trigger();
    }
    _delay_ms(100);
  }
  
  return 0;
}

void initTIM(void)
{
  /* Timer 1 counter */
  TCCR1B  |= (1 << CS11);
  TCCR1B  |= (1 << ICES1); // First capture is rising
  TIMSK   |= (1 << TICIE1);
  TCNT1   = 0;
}

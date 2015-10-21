/*
 * distance_meter.c
 *
 * Created: 7.10.2015 13:45:12
 *  Author: e1100983
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "include/USART_driver.h"

#define ECHO  PE7
#define TRIG  (1<<PE6)
#define CM    58

static uint16_t tim = 0;
static uint8_t flag = 0;
static uint8_t _ovf = 0;
static uint8_t c_echo = 0; // echo complete

//void initINT();
void initTIM();

void trigger()
{
  uint32_t  trig;
  uint8_t   loop;
  PORTE |= TRIG;
//  for(loop = 0; loop < 27; loop++)
//  {
    for(trig = 8; trig > 0; trig--)
    {}
//  }
  PORTE &= ~TRIG;
}


ISR(TIMER1_CAPT_vect)
{
  if(((TCCR1B >> ICES1) & 1) == 1)
  {
    TCNT1 = 0;
    TCCR1B &= ~(1 << ICES1);
  }
  else
  {
    tim = ICR1;
    c_echo = 1;
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
  uint32_t dist;

  DDRE &= ~(1 << ECHO);
  DDRE |= TRIG;

  initTIM();
  USART_Init();

  sei();
  trigger();

  while(1)
  {
    if(c_echo)
    {
      dist = tim/CM;
      USART_Transmit(USART_MODBUS, (tim >> 8));
      USART_Transmit(USART_MODBUS, tim);

      c_echo = 0;
      trigger();
    }

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

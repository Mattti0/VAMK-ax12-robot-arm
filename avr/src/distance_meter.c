/*
 * distance_meter.c
 *
 * Created: 7.10.2015 13:45:12
 *  Author: e1100983
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "include/USART_driver.h"

#define ECHO PE7
#define TRIG (1<<PE6)

static uint16_t tim = 0;
static uint8_t flag = 0;
static uint8_t _ovf = 0;
static uint8_t _flag = 0;

void initINT();
void initTIM();

ISR(INT7_vect)
{
  tim = TCNT1;
  
  if(!flag)
  {
    TCNT1 = 0; 
  }   
  else
    _flag  = 1;
  
  flag ^= 1;
}

ISR(TIMER1_OVF_vect)
{
  if(flag)
    _ovf++;
}

int main(void)
{
  uint8_t dist;
  uint32_t _tim;
  uint32_t trig;
  initINT();
  initTIM();
  USART_Init();
  sei();
  
  while(1)
  {
    if(_flag)
    {
      cli();
      //if(!_ovf)
        //_tim = ((uint32_t)(_ovf << 8)) | tim;
      //
      //else _tim = tim;
      //_flag = 0;
      //
      //dist = (uint8_t)(_tim / 58);
      //_ovf = 0;
      //
      //USART_Transmit(USART_MODBUS, dist);
      
      
      USART_Transmit(USART_MODBUS, (tim >> 8));
      USART_Transmit(USART_MODBUS, tim);
      _flag = 0;
      sei();
    }
    
    else
    {
      cli();
      PORTE |= TRIG;
      for(trig = 80000; trig < 0; trig--)
      {
      }
      PORTE &= ~TRIG;
      sei();
    }
  }
  
  return 0;
}

void initINT(void)
{
  DDRE &= ~(1 << ECHO);
  DDRE |= TRIG;
  
  PORTE |= TRIG;
  
  EICRB |= (1 << ISC70);
  EIMSK |= (1 << INT7);
}

void initTIM(void)
{
  /* Timer 1 counter */
  TCCR1A |= (1 << CS10);
  TIMSK = (1 << TOIE1);
  TCNT1 = 0;
}
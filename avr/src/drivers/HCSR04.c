/*
 * HCSR04.c
 *
 *  Created on: 4.11.2015
 *      Author: U321521
 */
#include "HCSR04.h"

static uint16_t timeUs = 0; // time is in uS because prescaler 8 is used
static uint8_t flag = 0;
static uint8_t _ovf = 0;
static uint8_t echo_complete = 0; // echo complete

uint16_t getDistance(void)
{
  uint16_t dist;
  
  echo_complete = 0;
  
  PORTE |= TRIG;
  _delay_us(10);
  PORTE &= ~TRIG;
  
  while (!echo_complete)
    ;
  
  dist = uStoCm(timeUs);
  
  return (dist);
}

uint16_t uStoCm(uint16_t us)
{
  uint16_t cm;
  
  cm = us / US_TO_CM_SCALER;
  
  return (cm);
}

uint16_t uStoMm(uint16_t us)
{
  uint16_t mm;
  
  mm = ((double)us / US_TO_CM_SCALER) * 10;
  
  return (mm);
}

/**
 * This function initializes atmel ports, timer and interrupt for sensor
 */
void HCSR04init(void)
{
  DDRD &= ~(1 << ECHO);
  DDRE |= TRIG;
  
  /* Timer 1 counter */
  TCCR1B |= (1 << CS11);
  TCCR1B |= (1 << ICES1); // First capture is rising
  TIMSK |= (1 << TICIE1);
  TCNT1 = 0;
  
  sei();
}

/**********************************
 * Interrupt vectors
 **********************************/
ISR(TIMER1_CAPT_vect)
{
  if (!flag)
  {
    TCNT1 = 0;
    TCCR1B &= ~(1 << ICES1);
    flag = 1;
  }
  else
  {
    timeUs = ICR1;
    echo_complete = 1;
    flag = 0;
    TCCR1B |= (1 << ICES1);
  }
}

ISR(TIMER1_OVF_vect)
{
  if (flag)
    _ovf++;
}

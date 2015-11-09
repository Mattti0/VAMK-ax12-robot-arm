/***************************************************************************
 *   Copyright (C) $Year$ by $Author: e1100983 $   *
 *   $Email$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*********************************************************************
 *
 * 1.  NAME
 *     $Source$
 * 2.  DESCRIPTION
 *
 * 6.  VERSIONS
 *       Original:
 *         $Date: 2014-03-29 17:41:28 +0200 (Sat, 29 Mar 2014) $ / $Author: e1100983 $
 *
 *       Version history: Veni , Vidi , Vici
 *
 *
 **********************************************************************/

/*-------------------------------------------------------------------*
 *    HEADER FILES                                                    *
 *--------------------------------------------------------------------*/
#include "HCSR04.h"

/*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
/* Control flags */
//#define DEBUG

/* Globaal constants */

/* Globaal variables */
static uint16_t timeUs = 0; // time is in uS because prescaler 8 is used
static uint8_t flag = 0;
static uint8_t _ovf = 0;
static uint8_t echo_complete = 0; // echo complete

/* Globaal structures */

/*-------------------------------------------------------------------*
 *    FUNCTION PROTOTYPES                                             *
 *--------------------------------------------------------------------*/
uint16_t uStoCm(uint16_t us);
uint16_t uStoMm(uint16_t us);
/*********************************************************************
 *    FUNCTIONS                                                     *
 **********************************************************************/

/*********************************************************************
 ;  F U N C T I O N    D E S C R I P T I O N
 ;---------------------------------------------------------------------
 ; NAME:
 ; DESCRIPTION:
 ;  Input:
 ;  Output:
 ;  Used global variables:
 ; REMARKS when using this function:
 ;*********************************************************************/
uint16_t GetDistance(void)
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

/*********************************************************************
 ;  F U N C T I O N    D E S C R I P T I O N
 ;---------------------------------------------------------------------
 ; NAME:
 ; DESCRIPTION:
 ;  Input:
 ;  Output:
 ;  Used global variables:
 ; REMARKS when using this function:
 ;*********************************************************************/
uint16_t uStoCm(uint16_t us)
{
  uint16_t cm;
  
  cm = us / US_TO_CM_SCALER;
  
  return (cm);
}

/*********************************************************************
 ;  F U N C T I O N    D E S C R I P T I O N
 ;---------------------------------------------------------------------
 ; NAME:
 ; DESCRIPTION:
 ;  Input:
 ;  Output:
 ;  Used global variables:
 ; REMARKS when using this function:
 ;*********************************************************************/
uint16_t uStoMm(uint16_t us)
{
  uint16_t mm;
  
  mm = ((double)us / US_TO_CM_SCALER) * 10;
  
  return (mm);
}

/*********************************************************************
 ;  F U N C T I O N    D E S C R I P T I O N
 ;---------------------------------------------------------------------
 ; NAME:
 ; DESCRIPTION: This function initializes atmel ports, timer and interrupt for sensor
 ;  Input:
 ;  Output:
 ;  Used global variables:
 ; REMARKS when using this function:
 ;*********************************************************************/
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

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
#include "USART_driver.h"


/*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
/* Control flags */
#define DEBUG

/* Globaal constants */

/* Globaal variables */

/* Globaal structures */

/*-------------------------------------------------------------------*
 *    FUNCTION PROTOTYPES                                             *
 *--------------------------------------------------------------------*/

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
Err_t USARTTransmit(uint8_t port, uint8_t data)
{
  Err_t err = ERROR;
  
  switch (port)
  {
    case 0:
      while (!(UCSR0A & (1 << UDRE0)))
        ;
      UDR0 = data;
      err = ERROR_OK;
      break;
      
    case 1:
      while (!(UCSR1A & (1 << UDRE1)))
        ;
      UDR1 = data;
      err = ERROR_OK;
      break;
      
    default:
      err = INVALID_PORT;
      break;
  }
  return err;
}

void USARTINIT()
{
  
  UBRR0H = 0x00;
  UBRR0L = ((XTAL / 16) / BAUD_SERVO) - 1;
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  UCSR1C |= (1 << UCSZ00) | (1 << UCSZ01);
  
  UBRR1H = 0x00;
  UBRR1L = ((XTAL / 16) / BAUD_MODBUS) - 1;
  UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
  UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
}

uint8_t USARTReceive(uint8_t port)
{
  switch (port)
  {
    case 0:
      while (!(UCSR0A & (1 << RXC)))
        ;
      return UDR0;
      break;
      
    case 1:
      while (!(UCSR1A & (1 << RXC)))
        ;
      return UDR1;
      break;
      
    default:
      break;
  }
  
  return 0;
}

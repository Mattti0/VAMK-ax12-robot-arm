/***************************************************************************
 *   Copyright (C) 2015 by Author: e1100983   *
 *     *
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
 *     control_motor.c
 * 2.  DESCRIPTION
 *
 * 6.  VERSIONS
 *       Original:
 *         5.10.2015
 *
 *       Version history: Veni , Vidi , Vici
 *
 *       RXD0 = PE0
 *       TXD0 = PE1
 *       RXEN = PE2
 *       TXEN = PE3
 *        
 *
 **********************************************************************/

/*-------------------------------------------------------------------*
 *    HEADER FILES                                                    *
 *--------------------------------------------------------------------*/
#include <avr/io.h>
#include "include/AX12.h"
#include "include/USART_driver.h"

/*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
/* Control flags */

/* Globaal constants */

/* Globaal variables */

/* Globaal structures */

/*-------------------------------------------------------------------*
 *    FUNCTION PROTOTYPES                                             *
 *--------------------------------------------------------------------*/

/*********************************************************************
 *    MAIN PROGRAM                                                      *
 **********************************************************************/

int main(void)
{
  USART_Init();

  PORTE = 0xFF;
  
  for(int i = 0; i < 0x500; i++)
  {
    
  }
  
  //turnMotor(servoTable[3], 150);
  //SetYX(72,10);
  //SetYX(56, 43);
  //SetYX(81, 55);
  //SetYX(0, 46);
} /* end of main */

/*********************************************************************
 *    FUNCTIONS                                                     *
 **********************************************************************/

/*********************************************************************
 ;	F U N C T I O N    D E S C R I P T I O N
 ;---------------------------------------------------------------------
 ; NAME:
 ; DESCRIPTION:
 ;	Input:
 ;	Output:
 ;  Used global variables:
 ; REMARKS when using this function:
 ;*********************************************************************/

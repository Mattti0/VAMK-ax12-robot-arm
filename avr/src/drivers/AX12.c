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
#include "AX12.h"

/*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
/* Control flags */
//#define DEBUG

/* Globaal constants */

/* Globaal variables */

/* Globaal structures */

/*-------------------------------------------------------------------*
 *    FUNCTION PROTOTYPES                                             *
 *--------------------------------------------------------------------*/

/*********************************************************************
 *    LOW LEVEL FUNCTIONS                                             *
 **********************************************************************/
/* Low level functions */
StatusErr_t idPing(uint8_t id);
StatusErr_t readData(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *rBuffer);
StatusErr_t writeData(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *wBuffer);
StatusErr_t regWrite(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *wBuffer);
StatusErr_t action();
StatusErr_t resetMotor(uint8_t id);
StatusErr_t syncWrite(uint8_t id);

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
StatusErr_t idPing(uint8_t id)
{
  return 0;
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
StatusErr_t readData(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *rBuffer)
{
  
  return 0;
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
StatusErr_t writeData(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *wBuffer)
{
  return 0;
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
StatusErr_t regWrite(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *wBuffer)
{
  Err_t err = ERROR;
  uint8_t check, i;
  uint8_t data[] = {0xFF, 0xFF, id, byteCount + 3, (uint8_t)REG_WRITE, regAddr};
  uint16_t checksum = 0;
  
  for (i = 2; i < 6; i++)
    checksum += data[i];
  
  if (byteCount > 0)
  {
    for (i = 0; i < byteCount; i++)
      checksum += *(wBuffer + i);
  }
  
  check = ~((uint8_t)checksum);
  
  TRAEN
  ;
  // Enable transmit
  
  for (i = 0; i < 6; i++)
  {
    err = USARTTransmit(USART_SERVO, data[i]);
    if (err != ERROR_OK)
      return err;
  }
  
  if (byteCount > 0)
  {
    for (i = 0; i < byteCount; i++)
    {
      err = USARTTransmit(USART_SERVO, *(wBuffer + i));
      if (err != ERROR_OK)
        return err;
    }
  }
  
  err = USARTTransmit(USART_SERVO, check);
  
  return 0;
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
StatusErr_t action()
{
  uint8_t check = ~(0xFE + 2 + (uint8_t)ACTION);
  uint8_t i;
  uint8_t data[] = {0xFF, 0xFF, 0xFE, 2, (uint8_t)ACTION, check};
  
  TRAEN
  ;
  
  for (i = 0; i < 6; i++)
  {
    USARTTransmit(USART_SERVO, data[i]);
  }
  
  return 0;
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
StatusErr_t resetMotor(uint8_t id)
{
  return 0;
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
StatusErr_t syncWrite(uint8_t id)
{
  return 0;
}

/*********************************************************************
 *    HIGH LEVEL FUNCTIONS                                             *
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
Err_t receiveStatus(uint8_t id, uint8_t *status, uint8_t *param, uint8_t *parcount)
{
  uint16_t start = 0;
  uint8_t i, checksum = 0, receiveChecksum = 0;
  
  /* Set PE2 to low & PE3 to high (enable receive) */
  RECEN
  ;
  
  do
  {
    start = (start << 8);
    start |= (uint16_t)USARTReceive(USART_SERVO);
  }
  while (start != 0xFFFF);
  
  if (id != USARTReceive(USART_SERVO))
    return INVALID_ID;
  
  *parcount = USARTReceive(USART_SERVO);
  
  *status = USARTReceive(USART_SERVO);
  
  if (*parcount > 2)
  {
    for (i = 0; i < (*parcount) - 2; i++)
    {
      *(param + i) = USARTReceive(USART_SERVO);
      checksum += *(param + i);
    }
  }
  
  receiveChecksum = USARTReceive(USART_SERVO);
  
  checksum += (id + *parcount + *status);
  checksum = ~checksum;
  
  if (checksum != receiveChecksum)
    return CRC_ERR;
  
  if (*status == 0)
    return ERROR_OK;
  
  else
    return STATUS_ERR;
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
Err_t TurnMotor(uint8_t id, uint16_t angle)
{
  Err_t err = ERROR;
  uint8_t errp, param, parcount;
  int8_t i;
  uint8_t data[] = {0xFF, 0xFF, id, 5, WRITE_DATA, GOALPOSITION_L, 0, 0, 0};
  uint16_t checksum = 0;
  
  if (angle > MAX_ANGLE || angle < MIN_ANGLE)
    return INVALID_RANGE;
  
  data[6] = (uint8_t)AngleLookupTable[angle];
  data[7] = (uint8_t)(AngleLookupTable[angle] >> 8);
  for (i = 2; i < 9; i++)
    checksum += data[i];
  data[8] = ~((uint8_t)checksum);
  
  TRAEN
  ;
  // Enable transmit
  
  for (i = 0; i < 9; i++)
  {
    err = USARTTransmit(USART_SERVO, data[i]);
    if (err != ERROR_OK)
      return err;
  }
  while (!(UCSR0A & (1 << TXC0)))
    ;
  
  err = receiveStatus(id, &errp, &param, &parcount);
  
  if (err == STATUS_ERR)
  {
    
  }
  
  return err;
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
Err_t SpinMotor(uint8_t id, uint16_t sp, uint8_t dir)
{
  /**
   * Wheel mode register is 11 bits
   * bit 0:9 speed (one unit is ~0,1% of maximum speed = 1000d ~ 100%)
   * bit 10  direction 0 to ccw and 1 to cw, when 0d or 1024d, stopped
   */
  uint16_t dirmask = 0x400;
  uint16_t speed;
  Err_t err = ERROR;
  uint8_t data[] = {0xFF, 0xFF, id, 5, WRITE_DATA, 0};
  
  if (sp < MIN_SPEED || sp > MAX_SPEED)
    return INVALID_RANGE;
  
  if (dir != ROTATE_CW)
    speed = dirmask | sp;
  
  return err;
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
void SetYX(uint8_t y, uint8_t x)
{
  uint8_t th1, th2;
  uint8_t msg[2];
  Err_t err;
  uint8_t errp, param, parcount;
  
  th2 = (uint8_t)(acos(
      (pow(x, 2) + pow(y, 2) - pow(AXLE_LEN, 2) - pow(AXLE_LEN, 2)) / (2 * AXLE_LEN * AXLE_LEN)) * 180.0
      / PI);
  th1 = (uint8_t)(asin(
      (y * (AXLE_LEN - AXLE_LEN * cos(th2)) - x * AXLE_LEN * sin(th2)) / (pow(x, 2) + pow(y, 2))) * 180.0
      / PI);
  
  msg[0] = (uint8_t)AngleLookupTable[th1];
  msg[1] = (uint8_t)(AngleLookupTable[th1] >> 8);
  regWrite(servoTable[2], GOALPOSITION_L, 2, msg);
  while (!(UCSR0A & (1 << TXC0)))
    ;
  
  msg[0] = (uint8_t)AngleLookupTable[th2];
  msg[1] = (uint8_t)(AngleLookupTable[th2] >> 8);
  regWrite(servoTable[3], GOALPOSITION_L, 2, msg);
  while (!(UCSR0A & (1 << TXC0)))
    ;
  
  action();
  
  //printf("TH0: %d; TH1: %d\n", th[0], th[1]);
  //turnMotor(servoTable[1], th[0]);
  //turnMotor(servoTable[2], th[1]);
//  msg[0] = (uint8_t)AngleLookupTable[th1];
//  msg[1] = (uint8_t)(AngleLookupTable[th1] >> 8);
//  regWrite(servoTable[1], GOALPOSITION_L, 2, msg);
//
//  msg[0] = (uint8_t)AngleLookupTable[th2];
//  msg[1] = (uint8_t)(AngleLookupTable[th2] >> 8);
//  regWrite(servoTable[2], GOALPOSITION_L, 2, msg);
//
//  action();
  
  //printf("TH0: %d; TH1: %d\n", th[0], th[1]);
  //turnMotor(servoTable[1], th[0]);
  //turnMotor(servoTable[2], th[1]);
}

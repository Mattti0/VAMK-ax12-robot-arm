/*
 * FreeModbus Libary: AVR Demo Application
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: demo.c,v 1.7 2006/06/15 15:38:02 wolti Exp $
 */

/* ----------------------- AVR includes -------------------------------------*/
#include "avr/io.h"
#include "avr/interrupt.h"
#include "USART_driver.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START   1000
#define REG_INPUT_NREGS   4
#define REG_HOLDING_START 100
#define REG_HOLDING_NREGS 10
/* ----------------------- Static variables ---------------------------------*/
static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegHoldStart = REG_HOLDING_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS];
static USHORT usRegHoldBuf[REG_HOLDING_NREGS];

/* ----------------------- Start implementation -----------------------------*/
int main(void)
{
  eMBErrorCode eStatus;

  eStatus = eMBInit(MB_RTU, 0x0A, 0, BAUD_MODBUS, MB_PAR_EVEN);

  sei( );

  /* Enable the Modbus Protocol Stack. */
  eStatus = eMBEnable();

  for (;;)
  {
    (void) eMBPoll();

    /* Here we simply count the number of poll cycles. */
    usRegInputBuf[0]++;
  }
}

eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress,
    USHORT usNRegs)
{
  eMBErrorCode eStatus = MB_ENOERR;
  int iRegIndex;

  if ((usAddress >= REG_INPUT_START)
      && (usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS))
  {
    iRegIndex = (int) (usAddress - usRegInputStart);
    while (usNRegs > 0)
    {
      *pucRegBuffer++ = (unsigned char) (usRegInputBuf[iRegIndex] >> 8);
      *pucRegBuffer++ = (unsigned char) (usRegInputBuf[iRegIndex] & 0xFF);
      iRegIndex++;
      usNRegs--;
    }
  }
  else
  {
    eStatus = MB_ENOREG;
  }

  return eStatus;
}

eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress,
    USHORT usNRegs, eMBRegisterMode eMode)
{
  eMBErrorCode  eStatus     = MB_ENOERR;
  short         inRegister  = (short) usNRegs;
  int           iRegIndex;
  USHORT        temp;

  if ((usAddress >= REG_HOLDING_START)
      && (usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS))
  {
    iRegIndex = (int) (usAddress - usRegHoldStart);
    switch (eMode)
    {
      /* Read current values and pass to protocol stack. */
      case MB_REG_READ:
        while (inRegister > 0)
        {
          *pucRegBuffer++ = (unsigned char) (usRegHoldBuf[iRegIndex] >> 8);
          *pucRegBuffer++ = (unsigned char) (usRegHoldBuf[iRegIndex] & 0xFF);
          iRegIndex++;
          inRegister--;
        }
        break;

        /* Update current register values. */
      case MB_REG_WRITE:
        while (inRegister > 0)
        {
          temp = *pucRegBuffer << 8;
          pucRegBuffer++;
          temp |= *pucRegBuffer;
          pucRegBuffer++;

          usRegHoldBuf[iRegIndex] = temp;

          iRegIndex++;
          inRegister--;
        }
        break;
    }

  }
  else
  {
    eStatus = MB_ENOREG;
  }

  return eStatus;
}

eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress,
    USHORT usNCoils, eMBRegisterMode eMode)
{
  return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress,
    USHORT usNDiscrete)
{
  return MB_ENOREG;
}

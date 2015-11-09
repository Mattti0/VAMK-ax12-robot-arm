/*
 * mb_func.c
 *
 *  Created on: 4.11.2015
 *      Author: U321521
 */

#include "mb.h"
#include "mbRegMap.h"

eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs)
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


eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode)
{
  eMBErrorCode  eStatus     = MB_ENOERR;
  short         inRegister  = (short) usNRegs;
  int           iRegIndex;
  USHORT        temp;

  if ((usAddress >= REG_HOLDING_START) && (usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS))
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


eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode)
{
  return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete)
{
  return MB_ENOREG;
}

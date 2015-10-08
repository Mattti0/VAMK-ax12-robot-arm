/*
 * AX12.c
 *
 *  Created on: 30.9.2015
 *      Author: suomima
 */

#include "AX12.h"

/**
 *  Low-level functions from AX commands
 */
StatusErr_t idPing(uint8_t id)
{
  return 0;
}

StatusErr_t ReadData(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *rBuffer)
{


  return 0;
}

StatusErr_t WriteData(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *wBuffer)
{
  return 0;
}

StatusErr_t RegWrite(uint8_t id, uint8_t regAddr, uint8_t byteCount, uint8_t *wBuffer)
{
  Err_t err = ERROR;
  uint8_t check, i;
  uint8_t data[] = {0xFF, 0xFF, id, byteCount+3, (uint8_t)REG_WRITE, regAddr};
  uint16_t checksum = 0;

  for (i = 2; i < 6; i++)
    checksum += data[i];

  if(byteCount > 0)
  {
    for(i = 0; i < byteCount; i++)
      checksum+= *(wBuffer+i);
  }

  check = ~((uint8_t) checksum);

  TRAEN // Enable transmit

  for (i = 0; i < 6; i++)
  {
    err = USART_Transmit(USART_SERVO, data[i]);
    if(err != ERROR_OK)
      return err;
  }

  if(byteCount > 0)
  {
    for(i = 0; i < byteCount; i++)
    {
      err = USART_Transmit(USART_SERVO, *(wBuffer+i));
      if(err != ERROR_OK)
        return err;
    }
  }

  err = USART_Transmit(USART_SERVO, check);

  return 0;
}

StatusErr_t Action()
{
  uint8_t check = ~(0xFE + 2 + (uint8_t)ACTION);
  uint8_t i;
  uint8_t data[] = {0xFF, 0xFF, 0xFE, 2, (uint8_t)ACTION, check};

  TRAEN

  for(i = 0; i < 6; i++)
  {
    USART_Transmit(USART_SERVO, data[i]);
  }

  return 0;
}

StatusErr_t Reset(uint8_t id)
{
  return 0;
}

StatusErr_t SyncWrite(uint8_t id)
{
  return 0;
}

/**
 *  Higher level functions
 */
Err_t receiveStatus(uint8_t id, uint8_t *status, uint8_t *param, uint8_t *parcount)
{
  uint16_t start = 0;
  uint8_t i, crc8 = 0, recCrc = 0;

  /* Set PE2 to low & PE3 to high (enable receive) */
  RECEN
  
  do
  {
    start = (start << 8);
    start |= (uint16_t)USART_Receive(USART_SERVO);
  }while(start != 0xFFFF);

  if(id != USART_Receive(USART_SERVO))
    return INVALID_ID;

  *parcount = USART_Receive(USART_SERVO);

  *status = USART_Receive(USART_SERVO);

  if(*parcount > 2)
  {
    for(i = 0; i < (*parcount)-2; i++)
    {
      *(param+i) = USART_Receive(USART_SERVO);
      crc8 += *(param+i);
    }
  }

  recCrc = USART_Receive(USART_SERVO);

  crc8 += (id + *parcount + *status);
  crc8 = ~crc8;

  if(crc8 != recCrc)
    return CRC_ERR;

  if(*status == 0)
    return ERROR_OK;

  else return STATUS_ERR;
}

Err_t turnMotor(uint8_t id, uint16_t angle)
{
  Err_t err = ERROR;
  uint8_t errp, param, parcount;
  int8_t i;
  uint8_t data[] =
  { 0xFF, 0xFF, id, 5, WRITE_VALUE, GOALPOSITION_L, 0, 0, 0 };
  uint16_t checksum = 0;

  if (angle > MAX_ANGLE || angle < MIN_ANGLE)
    return INVALID_RANGE;

  data[6] = (uint8_t) AngleLookupTable[angle];
  data[7] = (uint8_t)(AngleLookupTable[angle] >> 8);
  for (i = 2; i < 9; i++)
    checksum += data[i];
  data[8] = ~((uint8_t) checksum);

  TRAEN // Enable transmit

  for (i = 0; i < 9; i++)
  {
    err = USART_Transmit(USART_SERVO, data[i]);
    if(err != ERROR_OK)
      return err;
  }
  while(!(UCSR0A & (1 << TXC0)));

  err = receiveStatus(id, &errp, &param, &parcount);

  if(err == STATUS_ERR)
  {

  }

  return err;
}

Err_t spinMotor(uint8_t id, uint16_t sp, uint8_t dir)
{
  /**
   * Wheel mode register is 11 bits
   * bit 0:9 speed (one unit is ~0,1% of maximum speed = 1000d ~ 100%)
   * bit 10  direction 0 to ccw and 1 to cw, when 0d or 1024d, stopped
   */
  uint16_t dirmask = 0x400;
  uint16_t speed;
  Err_t err = ERROR;
  uint8_t data[] =
  { 0xFF, 0xFF, id, 5, WRITE_VALUE, 0};

  if (sp < MIN_SPEED || sp > MAX_SPEED)
    return INVALID_RANGE;

  if (dir != ROTATE_CW)
    speed = dirmask | sp;

  return err;
}

void SetYX(uint8_t y, uint8_t x)
{
  uint8_t th1, th2;
  uint8_t msg[2];
  Err_t err;
  uint8_t errp, param, parcount;
  uint8_t th1, th2;
  uint8_t msg[2];

  th2 = (uint8_t)(acos((pow(x, 2) + pow(y, 2) - pow(AXLE_LEN, 2) - pow(AXLE_LEN, 2))/ (2 * AXLE_LEN * AXLE_LEN)) * 180.0 / PI);
  th1 = (uint8_t)(asin((y*(AXLE_LEN - AXLE_LEN * cos(th2)) - x * AXLE_LEN* sin(th2)) / (pow(x,2) + pow(y,2))) * 180.0 / PI);

  msg[0] = (uint8_t)AngleLookupTable[th1];
  msg[1] = (uint8_t)(AngleLookupTable[th1] >> 8);
  RegWrite(servoTable[2], GOALPOSITION_L, 2, msg);
  while(!(UCSR0A & (1 << TXC0)));

  msg[0] = (uint8_t)AngleLookupTable[th2];
  msg[1] = (uint8_t)(AngleLookupTable[th2] >> 8);
  RegWrite(servoTable[3], GOALPOSITION_L, 2, msg);
  while(!(UCSR0A & (1 << TXC0)));

  Action();

  //printf("TH0: %d; TH1: %d\n", th[0], th[1]);
  //turnMotor(servoTable[1], th[0]);
  //turnMotor(servoTable[2], th[1]);
  msg[0] = (uint8_t)AngleLookupTable[th1];
  msg[1] = (uint8_t)(AngleLookupTable[th1] >> 8);
  RegWrite(servoTable[1], GOALPOSITION_L, 2, msg);

  msg[0] = (uint8_t)AngleLookupTable[th2];
  msg[1] = (uint8_t)(AngleLookupTable[th2] >> 8);
  RegWrite(servoTable[2], GOALPOSITION_L, 2, msg);

  Action();

  //printf("TH0: %d; TH1: %d\n", th[0], th[1]);
  //turnMotor(servoTable[1], th[0]);
  //turnMotor(servoTable[2], th[1]);
}

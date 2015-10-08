/*
 * err_t.h
 *
 *  Created on: 30.9.2015
 *      Author: suomima
 */

#ifndef ERR_T_H_
#define ERR_T_H_

typedef enum
{
  INVALID_ID = -6,
  STATUS_ERR,
  CRC_ERR,
  INVALID_PORT,
  INVALID_RANGE,
  ERROR,
  ERROR_OK = 0
} Err_t;

#endif

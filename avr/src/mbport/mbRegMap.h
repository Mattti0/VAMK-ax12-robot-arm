/*
 * mbRegMap.h
 *
 *  Created on: 9.11.2015
 *      Author: U321521
 */

#ifndef AVR_SRC_MBPORT_MBREGMAP_H_
#define AVR_SRC_MBPORT_MBREGMAP_H_

#define REG_INPUT_START   1000
#define REG_INPUT_NREGS   4
#define REG_HOLDING_START 100
#define REG_HOLDING_NREGS 10
/* ----------------------- Static variables ---------------------------------*/
static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegHoldStart = REG_HOLDING_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS];
static USHORT usRegHoldBuf[REG_HOLDING_NREGS];



#endif /* AVR_SRC_MBPORT_MBREGMAP_H_ */

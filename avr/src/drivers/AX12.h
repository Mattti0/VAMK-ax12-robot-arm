#ifndef INCLUDE_AX12_H_
#define INCLUDE_AX12_H_
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
#include <stdint.h>
#include "USART_driver.h"
#include "err_t.h"
/*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
/* Control macros */
#define RECEN PORTE |= (1 << 3); \
              PORTE &= ~(1 << 2)

#define TRAEN PORTE &= ~(1 << 3); \
              PORTE |= (1 << 2)

/* Globaal constants */
#define PI        3.14159265

#define MAX_ANGLE 300
#define MIN_ANGLE 0
#define MAX_SPEED 1023
#define MIN_SPEED 0

#define ROTATE_CW   1
#define ROTATE_CCW  0

#define START       0xFF


/*      Register                  Offset */
#define MODELNUMBER_L               0 
#define MODELNUMBER_H               1 
#define VERSIONOFFIRMWARE           2 
#define ID                          3 
#define BAUDRATE                    4 
#define RETURNDELAYTIME             5 
#define CWANGLELIMIT_L              6 
#define CWANGLELIMIT_H              7 
#define CCWANGLELIMIT_L             8 
#define CCWANGLELIMIT_H             9 
#define THEHIGHESTLIMITTEMPERATURE  11
#define THELOWESTLIMITVOLTAGE       12
#define THEHIGHESTLIMITVOLTAGE      13
#define MAXTORQUE_L                 14
#define MAXTORQUE_H                 15
#define STATUSRETURNLEVEL           16
#define ALARMLED                    17
#define ALARMSHUTDOWN               18
#define TORQUEENABLE                24
#define LED                         25
#define CWCOMPLIANCEMARGIN          26
#define CCWCOMPLIANCEMARGIN         27
#define CWCOMPLIANCESLOPE           28
#define CCWCOMPLIANCESLOPE          29
#define GOALPOSITION_L              30
#define GOALPOSITION_H              31
#define MOVINGSPEED_L               32
#define MOVINGSPEED_H               33
#define TORQUELIMIT_L               34
#define TORQUELIMIT_H               35
#define PRESENTPOSITION_L           36
#define PRESENTPOSITION_H           37
#define PRESENTSPEED_L              38
#define PRESENTSPEED_H              39
#define PRESENTLOAD_L               40
#define PRESENTLOAD_H               41
#define PRESENTVOLTAGE              42
#define PRESENTTEMPERATURE          43
#define REGISTERED                  44
#define MOVING                      46
#define LOCK                        47
#define PUNCH_L                     48
#define PUNCH_H                     49

/*! \def MODELNUMBER_L
 * \brief Lowest byte of model number R 12 (0X0C) */
/*! \def MODELNUMBER_H
 * \brief Highest byte of model number  R 0 (0X00)  */
/*! \def VERSIONOFFIRMWARE
 * \brief Information on the version of firmware  R - */
/*! \def ID
 * \brief ID of Dynamixel RW  1 (0X01)  */
/*! \def BAUDRATE
 * \brief Baud Rate of Dynamixel  RW  1 (0X01)  */
/*! \def RETURNDELAYTIME
 * \brief Return Delay Time RW  250 (0XFA)  */
/*! \def CWANGLELIMIT_L
 * \brief Lowest byte of clockwise Angle Limit  RW  0 (0X00)  */
/*! \def CWANGLELIMIT_H
 * \brief Highest byte of clockwise Angle Limit RW  0 (0X00)  */
/*! \def CCWANGLELIMIT_L
 * \brief Lowest byte of counterclockwise Angle Limit RW  255 (0XFF)  */
/*! \def CCWANGLELIMIT_H
 * \brief Highest byte of counterclockwise Angle Limit  RW  3 (0X03)  */
/*! \def THEHIGHESTLIMITTEMPERATURE
 * \brief Internal Limit Temperature   RW 70 (0X46) */
/*! \def THELOWESTLIMITVOLTAGE
 * \brief Lowest Limit Voltage  RW  60 (0X3C) */
/*! \def THEHIGHESTLIMITVOLTAGE
 * \brief Highest Limit Voltage RW  140 (0XBE)  */
/*! \def MAXTORQUE_L
 * \brief Lowest byte of Max. Torque  RW  255 (0XFF)  */
/*! \def MAXTORQUE_H
 * \brief Highest byte of Max. Torque RW  3 (0X03)  */
/*! \def STATUSRETURNLEVEL
 * \brief Status Return Level RW  2 (0X02)  */
/*! \def ALARMLED
 * \brief LED for Alarm RW  36(0x24)  */
/*! \def ALARMSHUTDOWN
 * \brief Shutdown for Alarm  RW  36(0x24)  */
/*! \def TORQUEENABLE
 * \brief Torque On/Off RW  0 (0X00)  */
/*! \def LED
 * \brief LED On/Off  RW  0 (0X00)  */
/*! \def CWCOMPLIANCEMARGIN
 * \brief CW Compliance margin  RW  1 (0X01)  */
/*! \def CCWCOMPLIANCEMARGIN
 * \brief CCW Compliance margin RW  1 (0X01)  */
/*! \def CWCOMPLIANCESLOPE
 * \brief CW Compliance slope RW  32 (0X20) */
/*! \def CCWCOMPLIANCESLOPE
 * \brief CCW Compliance slope  RW  32 (0X20) */
/*! \def GOALPOSITION_L
 * \brief Lowest byte of Goal Position  RW  - */
/*! \def GOALPOSITION_H
 * \brief Highest byte of Goal Position RW  - */
/*! \def MOVINGSPEED_L
 * \brief Lowest byte of Moving Speed (Moving Velocity) RW  - */
/*! \def MOVINGSPEED_H
 * \brief Highest byte of Moving Speed (Moving Velocity)  RW  - */
/*! \def TORQUELIMIT_L
 * \brief Lowest byte of Torque Limit (Goal Torque) RW  ADD14 */
/*! \def TORQUELIMIT_H
 * \brief Highest byte of Torque Limit (Goal Torque)  RW  ADD15 */
/*! \def PRESENTPOSITION_L
 * \brief Lowest byte of Current Position (Present Velocity)  R - */
/*! \def PRESENTPOSITION_H
 * \brief Highest byte of Current Position (Present Velocity) R - */
/*! \def PRESENTSPEED_L
 * \brief Lowest byte of Current Speed  R - */
/*! \def PRESENTSPEED_H
 * \brief Highest byte of Current Speed R - */
/*! \def PRESENTLOAD_L
 * \brief Lowest byte of Current Load R - */
/*! \def PRESENTLOAD_H
 * \brief Highest byte of Current Load  R - */
/*! \def PRESENTVOLTAGE
 * \brief Current Voltage R - */
/*! \def PRESENTTEMPERATURE
 * \brief Current Temperature R - */
/*! \def REGISTERED
 * \brief Means if Instruction is registered  R 0 (0X00)  */
/*! \def MOVING
 * \brief Means if there is any movement  R 0 (0X00)  */
/*! \def LOCK
 * \brief Locking EEPROM  RW  0 (0X00)  */
/*! \def PUNCH_L
 * \brief Lowest byte of Punch  RW  32 (0X20) */
/*! \def PUNCH_H
 * \brief Highest byte of Punch RW  0 (0X00)  */

static const uint8_t servoTable[] = {2, 12, 1, 3}; /*< Assigned servo id's */

static const uint16_t AngleLookupTable[] = {0x0, 0x3, 0x6, 0xA, 0xD, 0x11, 0x14, 0x17, 0x1B, 0x1E, 0x22,
    0x25, 0x28, 0x2C, 0x2F, 0x33, 0x36, 0x39, 0x3D, 0x40, 0x44, 0x47, 0x4B, 0x4E, 0x51, 0x55, 0x58, 0x5C,
    0x5F, 0x62, 0x66, 0x69, 0x6D, 0x70, 0x73, 0x77, 0x7A, 0x7E, 0x81, 0x84, 0x88, 0x8B, 0x8F, 0x92, 0x96,
    0x99, 0x9C, 0xA0, 0xA3, 0xA7, 0xAA, 0xAD, 0xB1, 0xB4, 0xB8, 0xBB, 0xBE, 0xC2, 0xC5, 0xC9, 0xCC, 0xCF,
    0xD3, 0xD6, 0xDA, 0xDD, 0xE1, 0xE4, 0xE7, 0xEB, 0xEE, 0xF2, 0xF5, 0xF8, 0xFC, 0xFF, 0x103, 0x106,
    0x109, 0x10D, 0x110, 0x114, 0x117, 0x11A, 0x11E, 0x121, 0x125, 0x128, 0x12C, 0x12F, 0x132, 0x136,
    0x139, 0x13D, 0x140, 0x143, 0x147, 0x14A, 0x14E, 0x151, 0x154, 0x158, 0x15B, 0x15F, 0x162, 0x165,
    0x169, 0x16C, 0x170, 0x173, 0x177, 0x17A, 0x17D, 0x181, 0x184, 0x188, 0x18B, 0x18E, 0x192, 0x195,
    0x199, 0x19C, 0x19F, 0x1A3, 0x1A6, 0x1AA, 0x1AD, 0x1B1, 0x1B4, 0x1B7, 0x1BB, 0x1BE, 0x1C2, 0x1C5,
    0x1C8, 0x1CC, 0x1CF, 0x1D3, 0x1D6, 0x1D9, 0x1DD, 0x1E0, 0x1E4, 0x1E7, 0x1EA, 0x1EE, 0x1F1, 0x1F5,
    0x1F8, 0x1FC, 0x1FF, 0x202, 0x206, 0x209, 0x20D, 0x210, 0x213, 0x217, 0x21A, 0x21E, 0x221, 0x224,
    0x228, 0x22B, 0x22F, 0x232, 0x235, 0x239, 0x23C, 0x240, 0x243, 0x247, 0x24A, 0x24D, 0x251, 0x254,
    0x258, 0x25B, 0x25E, 0x262, 0x265, 0x269, 0x26C, 0x26F, 0x273, 0x276, 0x27A, 0x27D, 0x280, 0x284,
    0x287, 0x28B, 0x28E, 0x292, 0x295, 0x298, 0x29C, 0x29F, 0x2A3, 0x2A6, 0x2A9, 0x2AD, 0x2B0, 0x2B4,
    0x2B7, 0x2BA, 0x2BE, 0x2C1, 0x2C5, 0x2C8, 0x2CB, 0x2CF, 0x2D2, 0x2D6, 0x2D9, 0x2DD, 0x2E0, 0x2E3,
    0x2E7, 0x2EA, 0x2EE, 0x2F1, 0x2F4, 0x2F8, 0x2FB, 0x2FF, 0x302, 0x305, 0x309, 0x30C, 0x310, 0x313,
    0x316, 0x31A, 0x31D, 0x321, 0x324, 0x328, 0x32B, 0x32E, 0x332, 0x335, 0x339, 0x33C, 0x33F, 0x343,
    0x346, 0x34A, 0x34D, 0x350, 0x354, 0x357, 0x35B, 0x35E, 0x362, 0x365, 0x368, 0x36C, 0x36F, 0x373,
    0x376, 0x379, 0x37D, 0x380, 0x384, 0x387, 0x38A, 0x38E, 0x391, 0x395, 0x398, 0x39B, 0x39F, 0x3A2,
    0x3A6, 0x3A9, 0x3AD, 0x3B0, 0x3B3, 0x3B7, 0x3BA, 0x3BE, 0x3C1, 0x3C4, 0x3C8, 0x3CB, 0x3CF, 0x3D2,
    0x3D5, 0x3D9, 0x3DC, 0x3E0, 0x3E3, 0x3E6, 0x3EA, 0x3ED, 0x3F1, 0x3F4, 0x3F8, 0x3FB, 0x3FE};
/* Globaal variables */

/* Globaal structures */

/*--------------------------------------------------------------------*
 *    TYPEDEFS			                                                  *
 *--------------------------------------------------------------------*/
typedef enum
{
  InstructionError = 0b01000000, /*<  Bit 6  When undefined Instruction is transmitted or the Action command is delivered without  */
  OverloadError = 0b00100000, /*<  Bit 5  When the current load cannot be controlled with the set maximum torque  */
  CheckSumError = 0b00010000, /*<  Bit 4  When the Checksum of the transmitted Instruction Packet is invalid  */
  RangeError = 0b00001000, /*<  Bit 3  When the command is given beyond the range of usage  */
  OverHeatingError = 0b00000100, /*<  Bit 2  When the internal temperature is out of the range of operating temperature set in  */
  AngleLimitError = 0b00000010, /*<  Bit 1  When Goal Position is written with the value that is not between CW Angle Limit and CCW Angle Limit  */
  InputVoltageError = 0b00000001 /*<  Bit 0  When the applied voltage is out of the range of operating voltage set in the Control Table  */
} StatusErr_t;

typedef enum
{
  PING_ = 0x01, /*< No action. Used for obtaining a Status Packet, 0 */
  READ_DATA = 0x02, /*< Reading values in the Control Table, 2 */
  WRITE_DATA = 0x03, /*< Writing values to the Control Table, 2 ~ */
  REG_WRITE = 0x04, /*< Similar to WRITE_DATA, but stays in standby mode until the ACTION instuction is given, 2 ~ */
  ACTION = 0x05, /*< Triggers the action registered by the REG_WRITE instruction, 0 */
  RESET = 0x06, /*< Changes the control table values of the Dynamixel actuator to the Factory Default Value settings, 0 */
  SYNC_WRITE = 0x83 /*< Used for controlling many Dynamixel actuators at the same time, 4 */
} RobotCommand_t;

/*-------------------------------------------------------------------*
 *    FUNCTION PROTOTYPES                                             *
 *--------------------------------------------------------------------*/
/* Higher level functions, able to call everywhere at program*/
Err_t receiveStatus(uint8_t id, uint8_t *status, uint8_t *param, uint8_t *parcount);
Err_t TurnMotor(uint8_t id, uint16_t angle);
Err_t SpinMotor(uint8_t id, uint16_t sp, uint8_t dir);
void SetYX(uint8_t y, uint8_t x);

#endif /* INCLUDE_AX12_H_ */

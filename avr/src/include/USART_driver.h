/*
 * USART_driver.h
 *
 * Created: 21.9.2015 12:04:31
 *  Author: e1100983
 */
#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include <avr/io.h>
#include "err_t.h"

#define XTAL 8000000 // MCU:n kellotaajuus
#define BAUD_SERVO  250000 // sarjaportin nopeus servolle
#define BAUD_MODBUS 38400 // sarjaportin nopeus modbussille

#define USART_MODBUS  1
#define USART_SERVO   0


Err_t USART_Transmit(uint8_t port, uint8_t data);
void USART_Init(void);
uint8_t USART_Receive(uint8_t port);

#endif /* USART_DRIVER_H_ */

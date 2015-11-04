/*
 * HCSR04.h
 *
 *  Created on: 6.10.2015
 *      Author: suomima
 */

#ifndef AVR_SRC_INCLUDE_HCSR04_H_
#define AVR_SRC_INCLUDE_HCSR04_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ECHO PD4
#define TRIG (1<<PE6)
#define US_TO_CM_SCALER  58

ISR(TIMER1_CAPT_vect);
ISR(TIMER1_OVF_vect);
uint16_t getDistance(void);
uint16_t uStoCm(uint16_t us);
uint16_t uStoMm(uint16_t us);
void HCSR04init(void);

#endif /* AVR_SRC_INCLUDE_HCSR04_H_ */

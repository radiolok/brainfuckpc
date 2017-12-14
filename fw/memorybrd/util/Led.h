/* 
* Led.h
*
* Created: 03.09.2017 22:48:51
* Author: radiolok
*/


#ifndef __LED_H__
#define __LED_H__

#define PANEL_LEFT 0
#define PANEL_RIGHT 1


#define LED_BLANK_PIN (1 << PB4)
#define NOT_LED_CLR_PIN (1 << PB5)
#define LED1_SET_PIN  (1 << PB6)
#define LED2_SET_PIN  (1 << PB7)


#include "driver/TLC5941.h"
#include "ram/ExternalRam.h"

uint8_t LedInit(void);
uint8_t LedStart(uint16_t _addr);
uint8_t LedTick(void);
uint8_t LedClear(void);
uint8_t LedWrite(uint8_t panel);

#endif //__LED_H__

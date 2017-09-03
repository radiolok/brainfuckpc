/* 
* TLC5941.h
*
* Created: 03.09.2017 23:27:25
* Author: radiolok
*/


#ifndef __TLC5941_H__
#define __TLC5941_H__

uint8_t TLC5941Init(void);

uint8_t TLC5941Clear(void);

/*Switch off all leds*/
uint8_t TLC5941Blank(void);

/*Switch off all leds*/
uint8_t TLC5941Show(void);

uint8_t TLC5941SetOutput(uint8_t out);


#endif //__TLC5941_H__

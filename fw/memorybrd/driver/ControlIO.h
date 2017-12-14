/* 
* ControlIO.h
*
* Created: 05.09.2017 22:59:13
* Author: radiolok
*/


#ifndef __CONTROLIO_H__
#define __CONTROLIO_H__

#include <io.h>

#define PIN_WR_RD (1 << PE5)
#define PORT_WR_RD (PINE)

#define PIN_MCU_WR_RD (1 << PE3)
#define PORT_MCU_WR_RD (PORTE)

#define PIN_MCU_OE (1 << PE2)
#define PORT_MCU_OE (PORTE)

#define PORT_MCU_INT (1 << PE4)
#define PIN_MCU_INT (1 << PE4)

#define PORT_STDOUT_WR (PINH)
#define PIN_STDOUT_WR (1 << PH7)

#define PORT_STDIN_RD (PINB)
#define PIN_STDIN_RD (1 << PB0)

#define PORT_STDIN_MODE (PINH)
#define PIN_STDIN_MODE (1 << PH6)

#define PORT_WORD_MODE (PING)
#define PIN_WORD_MODE (1 <<PG5) //16-bit mode enable


#define PORT_I0 (PINH)
#define PIN_I0 (1 << PH5)

#define PORT_I1 (PINH)
#define PIN_I1 (1 << PH4)

#define PORT_I2 (PINH)
#define PIN_I2 (1 << PH3)

#define PORT_I3 (PINH)
#define PIN_I3 (1 << PH2)

#define PORT_I4 (PINE)
#define PIN_I4 (1 << PE7)

#define PORT_I5 (PINE)
#define PIN_I5 (1 << PE6)

#define PORT_I6 (PINJ)
#define PIN_I6 (1 << PJ6)

#define PORT_I7 (PINJ)
#define PIN_I7 (1 << PJ5)

#define PORT_I8 (PINJ)
#define PIN_I8 (1 << PJ4)

#define PORT_I9 (PINJ)
#define PIN_I9 (1 << PJ3)

#define PORT_IO0 (PORTG)
#define PIN_IO0 (1<< PG1)

#define PORT_IO1 (PORTG)
#define PIN_IO1 (1 << PG0)

#define PORT_IO2 (PORTD)
#define PIN_IO2 (1 << PD7)

#define PORT_IO3 (PORTD)
#define PIN_IO3 (1 << PD6)

#define PORT_IO4 (PORTD)
#define PIN_IO4 (1 << PD7)

#define PORT_IO5 (PORTD)
#define PIN_IO5 (1 << PD7)

#define PORT_IO6 (PORTD)
#define PIN_IO6 (1 << PD7)

#define PORT_IO7(PORTD)
#define PIN_IO7 (1 << PD7)

#define PORT_IO8(PORTL)
#define PIN_IO8 (1 << PL7)

#define PORT_IO9(PORTL)
#define PIN_IO9 (1 << PL6)

#define PORT_IO10(PORTL)
#define PIN_IO10 (1 << PL5)

#define PORT_IO11(PORTL)
#define PIN_IO11 (1 << PL4)

#define PORT_IO12(PORTL)
#define PIN_IO12 (1 << PL3)

#define PORT_IO13(PORTL)
#define PIN_IO13 (1 << PL2)

#define PORT_IO14(PORTL)
#define PIN_IO14 (1 << PL1)

#define PORT_IO15(PORTL)
#define PIN_IO15 (1 << PL0)


#endif //__CONTROLIO_H__

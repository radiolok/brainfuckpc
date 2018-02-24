/*Copyright (c) 2013-2017, Artem Kashkanov
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted 
provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of 
conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other materials 
provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#ifndef __CONTROLIO_H__
#define __CONTROLIO_H__

#include <avr/io.h>

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

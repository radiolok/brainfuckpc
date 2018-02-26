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

#ifndef __LED_H__
#define __LED_H__

#include "../macros.h"
#include "../ram/ExternalRam.h"
#include "TLC5941.h"

#define LED_LATCH_1 0
#define LED_LATCH_2 1

void ledPoll(void);

void ledInit();

inline void ledLatch(uint8_t block)
{
	PORTB |= block? (1<<PB6) : (1 << PB7);
	_delay_us(2);
	PORTB &= ~((1<<PB6) | (1<<PB7));
}

inline void ledClr()
{
	PORTB &= ~(1 << PB5);
	_delay_us(2);
	PORTB |= (1 << PB5);
}

#endif //__LED_H__

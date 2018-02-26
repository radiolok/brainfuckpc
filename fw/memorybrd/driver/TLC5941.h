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


#ifndef __TLC5941_H__
#define __TLC5941_H__

#include "../macros.h"
#include <string.h>
#include "spi.h"

void TLC5941Init(void);

void TLC5941SetCurrent(uint8_t current);

void TLC5941SetColumn(uint8_t column);

inline void TLC5941SetBlank(void)
{
	PORTB |= (1 << PB4);
}

inline void TLC5941ReleaseBlank(void)
{
	PORTB &= ~(1 << PB4);
}

inline void TLC5941Update(void)
{
	PORTJ |= (1 << PJ3);
	_delay_us(2);
	PORTJ &= ~(1 << PJ3);
}

#endif //__TLC5941_H__

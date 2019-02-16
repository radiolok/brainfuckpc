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


#ifndef __LEDOUT_H__
#define __LEDOUT_H__

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "MTask.h"
#include "log.h"
const uint8_t ascii_table[] __attribute__((progmem)) =  
{
			//0		1		2	3		4	5		6	7		8	9	10		11	12		13	14		15
/*0x00-0x0F*/0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 
/*0x10-0x1F*/0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 
/*0x20-0x2F*/0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
/*0x30-0x3F*/0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
/*0x40-0x4F*/0x40, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x40, 0x40, 0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
/*0x50-0x5F*/0x73, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
/*0x60-0x6F*/0x40, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
/*0x70-0x7F*/0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
};

const static uint8_t segments[] = {0,3, 1,2,4,5};


class SegmentDisplay
{
//variables
public:
static SegmentDisplay& Instance()
{
	static SegmentDisplay instance;
	return instance;
}

	~SegmentDisplay();
	 void Init(uint8_t segmentCount, uint8_t _Base);
	 void Disp(void);//polled function
	 void operator() (const uint16_t data, const char* prefix, const uint8_t prefix_length);
	 
	 void operator () (const uint32_t data);
	 
	 void Poll();
private:


	enum class IC{digLow = 0, digHigh, segLow, segHigh};
	
		
	void Reset()
	{
		PORTD &= ~(1<< PD6);
		_delay_us(10);
		PORTD |= (1 << PD6);
	}
	
	void Set(SegmentDisplay::IC num)
	{
		uint8_t number = static_cast<uint8_t>(num);
		if (number <  4)//IC's number
		{
			PORTD &= ~((1<< PD2) | (1<< PD3) | (1 << PD4) | (1<< PD5))	;
			PORTD |= (1 << (number + 2));	
			_delay_us(10);
			PORTD &= ~(1 << (number + 2));
		}	
	}
	
	
	void SetSegment(uint8_t segment)
	{
		if (segment < m_segmentsCount)
		{
			uint8_t segmentPosition = 1 << segments[segment];
			uint8_t segmentLow = segmentPosition & 0x0F;
			uint8_t segmentHigh = (segmentPosition >> 4) & 0x0F;
			PORTC &= 0xF0;
			PORTC |= (segmentLow) & 0x0F;
			Set(IC::segLow);
			PORTC &= 0xF0;
			PORTC |= (segmentHigh) & 0x0F;
			Set(IC::segHigh);
		}
	}
	
	void SetSymbol(uint8_t Symbol)
	{
		uint8_t digitCode = 0;
		if (Symbol < 0x80)
		{
			digitCode =  pgm_read_byte(&ascii_table[(Symbol < 0x80)? Symbol : 0]);
		}
		uint8_t digitLow = digitCode & 0x0F;
		uint8_t digitHigh = (digitCode >> 4) & 0x0F;
		PORTC &= 0xF0;
		PORTC |= (digitLow) & 0x0F;
		Set(IC::digLow);
		PORTC &= 0xF0;
		PORTC |= (digitHigh) & 0x0F;
		Set(IC::digHigh);
	}
	
	uint8_t m_segmentsCount;
	uint8_t *m_segments;//symbols
	uint8_t m_currentSegment;//current digit
	uint8_t m_base;//base
	//uint16_t DataLog;
	//uint8_t DataDigit;
	
	//functions
	SegmentDisplay();
	

}; //SegmentDisplay


void SegmentDisplayPoll();

#endif //__LEDOUT_H__

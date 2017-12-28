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


template <uint8_t SegmentCount> class SegmentDisplay
{
//variables
public:
protected:
private:

//functions
public:
	SegmentDisplay();
	~SegmentDisplay();
	 void Init(uint8_t _Base);
	 void Disp(void);//polled function
	 operator() (const uint16_t data, const char* prefix, const uint8_t prefix_length);
	
protected:
private:

	SegmentDisplay( const SegmentDisplay &c );
	SegmentDisplay& operator=( const SegmentDisplay &c );

	void InitDriver();

	uint8_t m_digits[SegmentCount];//symbols
	uint8_t m_digit;//current digit
	uint8_t Base;//base
	uint16_t DataLog;
	uint8_t DataDigit;
	
	static uint8_t hexnumber_x[] PROGMEM ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};

}; //SegmentDisplay

#endif //__LEDOUT_H__

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


#include "SegmentDisplay.h"

// default constructor
SegmentDisplay::SegmentDisplay()
{
} //LedOut

// default destructor
SegmentDisplay::~SegmentDisplay()
{
} //~LedOut


void SegmentDisplay::Init(uint8_t _Base){
	DDRA|=0xF0;//digits
	DDRC|=0xFF;//segments
	memset(m_digits, sizeof(uint8_t)*SegmentCount);
	m_digit=0;//current_digit
	Base = _Base;//current base
}

SegmentDisplay::operator () (const uint16_t data, const char* prefix, const uint8_t prefix_length)
{

}


SegmentDisplay::InitDriver()
{
	DDRC |= (1<< PC0) | (1<< PC1) | (1 << PC2) | (1 << PC3);
	DDRD |= (1<< PD2) | (1<< PD3) | (1 << PD4) | (1<< PD5) | (1<< PD6);

}

/*
void SegmentDisplay::Disp(){//show symbols
	int16_t DataUnsignedLog=abs(DataLog);//hide 
	for (uint8_t digits_count=0;digits_count<LEDDIGITS;digits_count++)
	{//разделяем число на разряды по базе
		if (DataUnsignedLog>0){
			// Копируем очередную цифру в массив
			DataDigits[digits_count] = DataUnsignedLog % Base;
			// Переходим к следующей цифре
			DataUnsignedLog /= Base;
		}
		else//если в разряде нуль, то нуль(гашение старого числа).
		{
			DataDigits[digits_count]=0;
		}
	}
	PORTC=pgm_read_byte(&hexnumber_x[DataDigits[number_x]]);//выводим в порт представление числа
	if (number_x==DataDigit)//Разряд подсвечиваем
	PORTC|=0x80;
	PORTA=(1<<(4+number_x));//выбираем разряд
	number_x++;
	if (number_x>(LEDDIGITS-1)) number_x=0;
}*/
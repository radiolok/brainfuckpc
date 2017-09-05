/*Copyright (c) 2014, RLN-tech LLC
All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "Util.h"

uint8_t StrCat(char* str1, char* str2, uint8_t str1Cursor){
	uint8_t str2Cursor = 0;
	while (str2[str2Cursor] != 0x00){
		str1[str1Cursor] = str2[str2Cursor];
		str1Cursor++;
		str2Cursor++;
	}
	str1[str1Cursor] = 0x00;
	return str1Cursor;
}


void Itoa(int16_t value, char* string){
	uint8_t cursor=0;

	static const uint8_t base = 10;
	char tmpstring[9];
	int8_t tmpcursor=0;

	if (0 == value){
		string[cursor++] = 0x30; //"0"
		string[cursor++] = 0x00;// \n symbol!
		return;
	}

	if (value < 0){
		value = -value;
		string[cursor++] = 0x2D; //"-"
	}
	while (value > 0)
	{
		//
		tmpstring[tmpcursor++] = (value % base) + 0x30;
		//
		value /= base;
	}
	tmpcursor--;//last with value

	while (tmpcursor >= 0){
		string[cursor++] = tmpstring[tmpcursor--];
	}

	string[cursor] = 0x00;
}

void Ultoa(unsigned long value, char* string){

	Ltoa((signed long)value, string);

}

void Ltoa(int32_t value, char* string){
	uint8_t cursor=0;

	uint8_t Base = 10;
	char tmpstring[9];
	int8_t tmpcursor=0;

	if (0 == value){
		string[cursor++] = 0x30; //"0"
		string[cursor++] = 0x00;// \n symbol!
		return;
	}

	if (value < 0){
		value = -value;
		string[cursor++] = 0x2D; //"-"
	}
	while (value > 0)
	{
		//
		tmpstring[tmpcursor++] = (value % Base) + 0x30;
		//
		value /= Base;
	}
	tmpcursor--;//last with value

	while (tmpcursor >= 0){
		string[cursor++] = tmpstring[tmpcursor--];
	}

	string[cursor] = 0x00;
}


long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
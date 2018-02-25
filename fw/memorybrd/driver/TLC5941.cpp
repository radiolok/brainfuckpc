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


#include "TLC5941.h"

uint8_t currentLed = 0;
uint8_t ledArray[12];

uint8_t currentDC = 32;//6-bit, 0 to 63.
uint8_t shift[4] = {0, 6, 4, 2};

void TLC5941Poll(void)
{
	//recalculate array:
	uint8_t base = currentLed >> 4;
	uint8_t delim = currentLed % 4;
	uint8_t currentByte = base * 3 + (delim == 0 ? (delim - 1) : 0);
	uint8_t bitshift = shift[delim];
	switch (bitshift){
		case 0:
			ledArray[currentByte] &= 0xC0;
		break;	
		case 2:
			ledArray[currentByte] &= 0x03;
		break;
		case 4:
			ledArray[currentByte] &= 0x0F;
			ledArray[currentByte + 1] &= 0xFC;
		break;		
		case 6:
			ledArray[currentByte] &= 0x3F;
			ledArray[currentByte + 1] &= 0xF0;
		break;
	};	
	currentLed++;
	if (currentLed > 15)
	{
		currentLed = 0;
	}
	base = currentLed >> 4;
	delim = currentLed % 4;
	currentByte = base * 3 + (delim == 0 ? (delim - 1) : 0);
	bitshift = shift[delim];
	switch (bitshift){
		case 0:
			ledArray[currentByte] |= currentDC;
		break;
		case 2:
			ledArray[currentByte] |= (currentDC << 2) & 0xFC;
		break;
		case 4:
			ledArray[currentByte] |= (currentDC << 4) & 0xF0;
			ledArray[currentByte + 1] |= (currentDC >> 4) & 0x03;
		break;
		case 6:
			ledArray[currentByte] |= (currentDC << 6) & 0xC0;
			ledArray[currentByte + 1] |= (currentDC >> 2) & 0x0F;
		break;
	};
	
}

uint8_t TLC5941Init(void)
{
	uint8_t status = 0;
	spi_init();
	TLC5941SetBlank();
	for (uint8_t i = 0; i < 12; ++i)
	{
		ledArray[i] = 0;
	}
	TLC5941ReleaseBlank();
return status;
}

uint8_t TLC5941Blank(void)
{
	uint8_t status = 0;

	return status;
}

uint8_t TLC5941Show(void)
{
	uint8_t status = 0;

	return status;
}

uint8_t TLC5941Clear(void)
{
uint8_t status = 0;

return status;
}

uint8_t TLC5941SetOutput(uint8_t out)
{
	uint8_t status = 0;

	return status;	
}



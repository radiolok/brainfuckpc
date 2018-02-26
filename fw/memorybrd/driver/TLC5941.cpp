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


uint8_t currentDC = 32;//6-bit, 0 to 63.
uint8_t shift[4] = {0, 6, 4, 2};
	
uint8_t tlcDataRegister[4][3] = 
{
	{
		0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00
	}
};

void TLC5941Poll(void)
{
	//recalculate array:
	uint8_t zeroes_prefix = (currentLed >> 4) * 3;
	uint8_t bytes_sended = 0;
	for (uint8_t i = 0; i < zeroes_prefix; ++i)
	{
		spi_sendByte(0);
		++bytes_sended;
	}
	uint8_t delim = currentLed % 4;
	for (uint8_t i = 0; i < 3; ++i)
	{
		spi_sendByte(tlcDataRegister[delim][i]);
		++bytes_sended;
	}
	for (bytes_sended < 12; ++bytes_sended)
	{
		spi_sendByte(0);
	}
}

void TLC5941updateArray(uint8_t data)
{
	memset(tlcDataRegister, 0, 12);//clear data
	tlcDataRegister[0][0] = data & 0x3F;
	
	tlcDataRegister[1][0] = (data << 6) & 0xC0;
	tlcDataRegister[1][1] = (data >> 2) & 0x0F;

	tlcDataRegister[2][1] = (data << 4) & 0xF0;
	tlcDataRegister[2][2] = (data >> 4) & 0x03;
	
	tlcDataRegister[3][2] = (data << 2) & 0xFC;

}

uint8_t TLC5941Init(void)
{
	uint8_t status = 0;
	spi_init();
	TLC5941SetBlank();

	TLC5941updateArray(currentDC);

	for (uint8_t i = 0; i < 12; ++i)
	{
		spi_sendByte(0);
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



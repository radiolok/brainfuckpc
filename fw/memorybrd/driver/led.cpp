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


#include "led.h"

uint8_t currentLed = 0;

uint16_t startAddr = 0;

/*
MOSI - PB2
CLK - PB1
BLANK - PB4
XLAT - PJ3
OE - PE6

*/

void ledInit()
{
	DDRB |= (1 << PB4);
	DDRJ |= (1 << PJ3);
	DDRE |= (1 << PE6);
	spi_init();
	ledClr();
	//TLC5941Init();
	log_trace("ledInit Done");
}

void ledClr()
{
	PORTB &= ~(1 << PB4);
	_delay_us(2);
	PORTB |= (1 << PB4);
}


void ledLatch()
{
	PORTJ |= (1 << PJ3);
	_delay_us(2);
	PORTJ &= ~(1 << PJ3);
}

void ledEnable(uint8_t mode)
{
	if (mode == false)
	{
		PORTE |= (1 << PE6);
	}
	else
	{
		PORTE &= ~ (1 << PE6);
	}
}

void ledSetStartAddress(uint16_t addr)
{
	startAddr = addr;
	ledEnable(true);
}

void ledSendDataToColumn(uint16_t data, uint8_t column)
{
	if (column < 8)
	{
		spi_sendByte(0);
		spi_sendByte(1 << column);

	}
	else
	{
		spi_sendByte(1 << (column - 8));
		spi_sendByte(0);
				
	}
	spi_sendByte(high(data));
	spi_sendByte(low(data));
}

void ledPoll(void)
{
	ledClr();
	uint16_t data = 0;
	if (ramReadWord(startAddr + currentLed, &data) == 0)
	{
		ledSendDataToColumn(data, currentLed);
		currentLed++;
		if (currentLed > 15)
		{
			currentLed = 0;
		}
	}
	ledLatch();

}

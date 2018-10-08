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

#include "dataIO.h"

uint16_t ioMcuReadDataFromBus(void)
{
	return 0;
}

void ioMcuWriteDataToBus(uint16_t data)
{
	//TODO: add lock
	DDRF = 0xFF;
	DDRK = 0xFF;
	PORTF = low(data);
	//dbg_trace_val("ramSetAddress = low:", PINA);
	PORTK = high(data);
	//dbg_trace_val("ramSetAddress = high:", PINC);
}

void ioMcuReleaseDataBus(void)
{
	DDRF = 0x00;
	DDRK = 0x00;
	PORTF = 0x00;
	PORTK = 0x00;
}

uint16_t ioMcuReadAddrFromBus(void)
{
	return 0;
}

void ioMcuWriteAddrToBus(uint16_t addr)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	PORTA = low(addr);
	//dbg_trace_val("ramSetAddress = low:", PINA);
	PORTC = high(addr);
	//dbg_trace_val("ramSetAddress = high:", PINC);
}

void ioMcuReleaseAddrBus(void)
{
	DDRA = 0x00;
	DDRC = 0x00;
}



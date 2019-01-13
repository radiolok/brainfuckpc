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

#include "macros.h"

#include "MTask.h"
#include "log.h"
#include "uart.h"
#include "ram/ExternalRam.h"
#include "driver/led.h"
#include "driver/pinIO.h"
#include "midi.h"

static uint32_t SCHEDULER_PERIOD = 1;//ms

uint16_t helloworldApp[44] = {
	0x4fff, 0x200a ,0x600b ,0x4001 ,0x2007 ,0x4001 ,0x200a ,0x4001 ,0x2003 ,0x4001 ,0x2001 ,
	0x5ffc ,0x3fff ,0x9ff5 ,0x4001 ,0x2002 ,0x1002 ,0x4001 ,0x2001 ,0x1002 ,0x2007 ,0x1002 ,
	0x1002 ,0x2003 ,0x1002 ,0x4001 ,0x2002 ,0x1002 ,0x5ffe ,0x200f ,0x1002 ,0x4001 ,0x1002 ,
	0x2003 ,0x1002 ,0x3ffa ,0x1002 ,0x3ff8 ,0x1002 ,0x4001 ,0x2001 ,0x1002 ,0x4001 ,0x1002 };

uint16_t check[44] = {0x00};



uint8_t getWriteMode()
{
	static uint8_t Write_mode = 0;
	static uint8_t Write_mode_old = 0;
	Write_mode = getInputPin((uint8_t)PinExtIn::WR);
	if (Write_mode != Write_mode_old)
	{
		if (Write_mode == true)
		{
			log_trace("Write data to RAM!");
		}
		else
		{
			log_trace("Read data from RAM!");
		}
	}
	Write_mode_old = Write_mode;
	return Write_mode;
}

uint8_t getSyncMode()
{
	static uint8_t Sync_mode = 0;
	static uint8_t Sync_mode_old = 0;
	Sync_mode = getInputPin((uint8_t)PinExtIn::Sync);
	if (Sync_mode != Sync_mode_old)
	{
		if (Sync_mode == true)
		{
			if (getWriteMode() == true)
			{
				uart_puts("begin->RAM->Sync->Write: ");
				uart_print((int16_t)(ramGetAddress() ),16);
				uart_puts(" - ");
				uart_print((int16_t)(ramGetData() ),16);
				uart_putc('\n');

			}
			else
			{
				uart_puts("begin->RAM->Sync->Read: ");
				uart_print((int16_t)(ramGetAddress() ),16);
				uart_puts(" - ");
				uart_print((int16_t)(ramGetData() ),16);
				uart_putc('\n');
			}			
		}
		else
		{
			log_trace("end->RAM->Sync: ");
		}
	}
	Sync_mode_old = Sync_mode;
	return Sync_mode;
}

uint8_t getStdInMode()
{
	static uint8_t Stdin_mode = 0;
	static uint8_t Stdin_mode_old = 0;
	Stdin_mode = getInputPin((uint8_t)PinExtIn::STDIN_MODE);
	if (Stdin_mode != Stdin_mode_old)
	{
		if (Stdin_mode == true)
		{
			log_trace("StdIn Mode 16 bit!");
		}
		else
		{
			log_trace("StdIn Mode 8 bit!");
		}
	}
	Stdin_mode_old = Stdin_mode;
	return Stdin_mode;
}

uint8_t getStdRd()
{
	static uint8_t Stdin_mode = 0;
	static uint8_t Stdin_mode_old = 0;
	Stdin_mode = getInputPin((uint8_t)PinExtIn::STDIN_RD);
	if (Stdin_mode != Stdin_mode_old)
	{
		if (Stdin_mode == true)
		{
			log_trace("begin>getc()!");
		}
		else
		{
			log_trace("end>getc()!");
		}
	}
	Stdin_mode_old = Stdin_mode;
	return Stdin_mode;
}

uint8_t getStdWr()
{
	static uint8_t Stdin_mode = 0;
	static uint8_t Stdin_mode_old = 0;
	Stdin_mode = getInputPin((uint8_t)PinExtIn::STDOUT_WR);
	if (Stdin_mode != Stdin_mode_old)
	{
		if (Stdin_mode == true)
		{
			log_trace("begin>putc()!");
		}
		else
		{
			log_trace("end>putc()!");
		}
	}
	Stdin_mode_old = Stdin_mode;
	return Stdin_mode;
}

void loadTestFw()
{
	for (uint16_t addr = 0; addr < 0x1000; ++addr)
	{
		ramWriteWord(addr, (addr % 2)? 0xAAAA : 0x5555);
	
	}
}


void loadHelloWorld()
{
	ramWriteWordBuffer(0, helloworldApp, sizeof(helloworldApp)/sizeof(uint16_t));
	
	ramReadWordBuffer(0, check, sizeof(check)/sizeof(uint16_t));
	
	size_t result = memcmp(helloworldApp, check, 88);
	
	if (!result)
	{
		log_trace("Hello World Application loaded succesfully!");
	}
	else
	{
		log_trace_val("Hello World Application loading failed!", result);
		for (uint16_t addr = 0; addr < 44; ++addr)
		{
			uart_puts("(0x");
			uart_print((int16_t)(addr ),16);
			uart_puts(")\t");
			uart_print((int16_t)helloworldApp[addr],16);
			uart_puts("\t");
			uart_print((int16_t)check[addr],16);
			uart_putc('\n');
		}
	}
}

void ramChecker()
{
	static uint16_t addr = sizeof(helloworldApp)/sizeof(uint16_t);
	if (getSyncMode() == false)
	{
		ramWriteWord(addr ,  addr);
		if (addr){
			uint16_t result;
			ramReadWord(addr, &result);
			uart_puts("(0x");
			uart_print((int16_t)(addr ),16);
			uart_puts(")=0x");
			uart_print((int16_t)result,16);
			
			if (( addr) == result)
			{
				uart_puts(" OK!");
			}
			else
			{
				uart_puts("Fail!");
			}
			uart_putc('\n');
		}
		addr++;	
	}
}



void GPinOutChecker()
{
	static bool state = 0;
	//log_trace("GPinOutChecker");
	for (uint8_t pin = 0; pin < 16; ++pin)
		SetOutputPin(pin, state);
	state ^= 1;
}


void inputChecker()
{
	getWriteMode();
	getSyncMode();
	getStdInMode();
	getStdWr();
	getStdRd();	
}


int main(void)
{
	sei();
	//setupTimer();
	//noteOn(1);
	//startMidi();
	uart_init(UART_BAUD_SELECT(38400, F_CPU));
	log_trace("uart started");
	MTask::Instance().Init(SCHEDULER_PERIOD, F_CPU);	
	log_trace("MTask Inited");
	ramInit();
	ledInit();
	//loadHelloWorld();
	loadTestFw();

	MTask::Instance().Add(GPinOutChecker, NULL, 100);
	//MTask::Instance().Add(ramChecker, NULL, 10);
	MTask::Instance().Add(inputChecker, NULL, 1);
	//Currently unavailable
	MTask::Instance().Add(ledPoll, NULL, 1);
	MTask::Instance().Start();
	log_trace("Dead");

}


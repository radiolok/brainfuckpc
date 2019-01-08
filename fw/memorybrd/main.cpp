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
	0x2fff, 0x000a ,0x800b ,0x2001 ,0x0007 ,0x2001 ,0x000a ,0x2001 ,0x0003 ,0x2001 ,0x0001 ,
	0x3ffc ,0x1fff ,0xbff5 ,0x2001 ,0x0002 ,0x6000 ,0x2001 ,0x0001 ,0x6000 ,0x0007 ,0x6000 ,
	0x6000 ,0x0003 ,0x6000 ,0x2001 ,0x0002 ,0x6000 ,0x3ffe ,0x000f ,0x6000 ,0x2001 ,0x6000 ,
	0x0003 ,0x6000 ,0x1ffa ,0x6000 ,0x1ff8 ,0x6000 ,0x2001 ,0x0001 ,0x6000 ,0x2001 ,0x6000};

uint16_t check[44] = {0x00};

void loadHelloWorld()
{
	ramWriteWordBuffer(0, helloworldApp, sizeof(helloworldApp)/sizeof(uint16_t));
	
	ramReadWordBuffer(0, check, sizeof(check)/sizeof(uint16_t));
	
	if (!memcmp(helloworldApp, check, sizeof(helloworldApp)))
	{
		log_trace("Hello World Application loaded succesfully!");
	}
	else
	{
		log_trace("Hello World Application loading failed!");
	}
}

void ramChecker()
{
	static uint16_t addr = sizeof(helloworldApp)/sizeof(uint16_t);
	ramWriteWord(addr , 0xFFFF - addr);
	if (addr){
		uint16_t result;
		ramReadWord(addr, &result);
		uart_puts("(0x");
		uart_print((int16_t)(addr ),16);
		uart_puts(")=0x");
		uart_print((int16_t)result,16);
		
		if ((0xFFFF - addr) == result)
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

void GPinOutChecker()
{
	static bool state = 0;
	//log_trace("GPinOutChecker");
	for (uint8_t pin = 0; pin < 16; ++pin)
		SetOutputPin(pin, state);
	state ^= 1;
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
	loadHelloWorld();

	MTask::Instance().Add(GPinOutChecker, NULL, 100);
	//MTask::Instance().Add(ramChecker, NULL, 200);
	//Currently unavailable
	//MTask::Instance().Add(ledPoll, NULL, 1);
	MTask::Instance().Start();
	log_trace("Dead");

}


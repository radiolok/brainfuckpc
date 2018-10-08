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

uint16_t addr = 0;

void ramChecker()
{
	ramWriteWord(addr & 0x1F, addr);
	if (addr){
		uint16_t result = ramReadWord(addr & 0x1F);
		uart_puts("(0x");
		uart_print((int16_t)(addr & 0x1F),16);
		uart_puts(")=0x");
		uart_print((int16_t)result,16);
		uart_putc('\n');
	}
	addr++;

}

int main(void)
{
	sei();
	startMidi();
	//uart_init(UART_BAUD_SELECT(38400, F_CPU));
	//log_trace("uart started");
	//MTask::Instance().Init(SCHEDULER_PERIOD, F_CPU);
	//log_trace("MTask Inited");
	//ramInit();
	//ledInit();
	//MTask::Instance().Add(ramChecker, NULL, 10);
	//MTask::Instance().Add(ledPoll, NULL, 10);
	//MTask::Instance().Start();
	//log_trace("Dead");
    while (1) 
    {
		if (getInputPin((uint8_t)PinExtIn::I2))
		{
			//TMP_WR
			SetOutputPin((uint8_t)PinExtOut::IO11, HIGH);
			_delay_us(900);
			SetOutputPin((uint8_t)PinExtOut::IO11, LOW);
			_delay_us(2500);
			//IP_WR
			SetOutputPin((uint8_t)PinExtOut::IO10, HIGH);
			_delay_us(900);
			SetOutputPin((uint8_t)PinExtOut::IO10, LOW);
			_delay_us(1000);
			//log_trace("tick");
		}
    }
}


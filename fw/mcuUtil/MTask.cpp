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



#include "MTask.h"

#define TEN_MS_TICK (6) //0.01мс

uint32_t tickPeriod = TEN_MS_TICK;
#define PRESC_COUNT (5)
uint16_t prescalers[PRESC_COUNT] = {1, 8, 64, 256, 1024};

MTask::MTask()
{

}

MTask::~MTask(){

}
void MTask::Init(uint32_t period, uint32_t cpu_frequency){
	//calc nearest prescaler:
	uint32_t tick_period = (cpu_frequency / 1000) * period;
	uint8_t prescaler = 0;
	uint32_t result = tick_period;
	while (result > 0xFF)
	{
		result = tick_period / prescalers[prescaler];
		prescaler++;
		if (prescaler > PRESC_COUNT)
		{
			break;
		}
	}
	if (prescaler == 0)
	{
		prescaler = 1;
	}
	if (result == 0)
	{
		result = 1;
	}
	ActiveApp = 0;
	TCCR1A |= (1<<WGM10);//PWM 8-bit with 0xFF on TOP
	TCCR1B |= (1<<WGM12);
	
	TCCR1B |= prescaler & 0x07;
	tickPeriod = 255 - result;
	TCNT1 = tickPeriod;//1мс
	for (uint8_t slot = 0; slot < PSLOTS; slot++)
	{//clear all slots
		Release(slot);
	}	
}

void MTask::Start(){
	
	HwStart();
	
	while(1)
	{//SwRoutine
		//Buttons.Search(m_timemillis);
		for (uint8_t slot = 0; slot < PSLOTS; slot++)
		{
			if ((App[slot].poll != 0)&&(App[slot].time != 0))
			{
				if (App[slot].tick == 0)
				{
					App[slot].tick = App[slot].time;
					(*App[slot].poll)();//non-interrupt work
				}
			}
		}	
	}
}


void MTask::HwStart()
{
	m_timemillis=0;//reset time counter
#if  defined(__AVR_ATmega8__)
	TIMSK |= (1<<TOIE1);
#else
	TIMSK1 |= (1<<TOIE1);
#endif
}

int8_t  MTask::Add(void (*_poll)(), void (*_hw)(), uint32_t periodic)
{
	uint8_t slot = getFreeSlot();
	if (PSLOTS > slot){
		App[slot].poll = _poll;
		App[slot].hw = _hw;
		App[slot].time = periodic;
		App[slot].tick = periodic;
	}
	else
	{
		return -1;
	}
	return 0;
}

void MTask::Release(uint8_t slot)
{
	if (PSLOTS > slot){
		App[slot].poll = 0;
		App[slot].hw = 0;
		App[slot].time = 0;
		App[slot].tick = 0;
	}
}

void MTask::HwStop()//Stop scheduler
{
	TCCR1B &= ~((1<<CS11) | (1<<CS10));
	
#if  defined(__AVR_ATmega8__)
	TIMSK &= ~(1<<TOIE1);
#else
	TIMSK1 &= ~(1<<TOIE1);
#endif
}

uint32_t MTask::Millis(){
	return m_timemillis;
	
}

void MTask::Search(){
	m_timemillis++;
	for (uint8_t slot = 0; slot < PSLOTS; slot++)
	{//count times
		if (App[slot].poll!= 0){//If App is defined
			if(App[slot].tick != 0){//And time is not yet
				App[slot].tick--;//Count to zero
			}
		}
	} 
}

uint8_t state = 0;



ISR(TIMER1_OVF_vect) {
		if (state)
		{
			state = 0;
		}
		else {
			state = 1;
		}
	TCNT1 = tickPeriod;//update tick
	MTask::Instance().Search();
 }  


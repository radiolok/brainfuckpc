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


MTask::MTask()
{

}

MTask::~MTask(){

}
void MTask::Setup(uint32_t period, uint32_t frequency){
		tickPeriod = (period * TEN_MS_TICK)/10;
		if (tickPeriod == 0)
		{
			tickPeriod = 1;
		}
	ActiveApp = 0;
	TCCR1A |= (1<<WGM10);//PWM 8-bit with 0xFF on TOP
	TCCR1B |= (1<<WGM12);
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
	TCCR1B |= (1<<CS11) | (1<<CS10);//prescaler at 64.<==TODO: rewrite to any frequency
	TIMSK1 |= (1<<TOIE1);
}

void MTask::Add(uint8_t slot, void (*_f)(), uint32_t periodic)
{
	if (PSLOTS > slot){
		App[slot].poll = _f;
		App[slot].hw = 0;
		App[slot].time = periodic;
		App[slot].tick = periodic;
	}
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
	TIMSK1 &= ~(1<<TOIE1);
}

uint32_t MTask::Millis(){
	return m_timemillis;
	
}

void MTask::Search(){
	m_timemillis++;
	for (uint8_t slot = 0; slot < PSLOTS; slot++)
	{//count times
		if (App[slot].hw != 0){//If App is defined
			if(App[slot].tick != 0){//And time is not yet
				App[slot].tick--;//Count to zero
			}
		}
	} 
}


ISR(TIMER1_OVF_vect) {
	TCNT1 = tickPeriod;//update tick
	MTaskSingleton::Instance().Search();
 }  


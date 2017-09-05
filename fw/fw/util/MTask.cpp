/*
 * taskmanager.cpp
 *
 * Created: 02.01.2013 18:30:26
 *  Author: Artem
 */ 

#include "Apps/MApp.h"

#include "MTask.h"

#define TIMETICK (6) //0.01мс

MTask::MTask()//установка таймера.
{
	TCCR5A |= (1<<WGM50);//PWM 8-bit with 0xFF on TOP
	TCCR5B |= (1<<WGM52);
	TCNT5 = TIMETICK;//1мс
	for (uint8_t slot = 0; slot < PSLOTS; slot++)
	{
		AppPtr[slot].app = 0;
		AppPtr[slot].period = 0;
	}
}

MTask::~MTask(){

}

void MTask::Start(){
	
	HwStart();
	
	while(1){//SwRoutine
		for (uint8_t slot = 0; slot < PSLOTS; slot++)
		{
			if (AppPtr[slot].app != 0){
				AppPtr[slot].app->SwClock(Millis);
			}
		}	
	}
}


void MTask::HwStart()//разрешает работу диспетчера
{
	Millis=0;//Сброс значения
	TCCR5B |= (1<<CS51) | (1<<CS50);//прескалер на 64.
	TIMSK5 |= (1<<TOIE5);
}

void MTask::Add(MApp* _app, uint8_t slot)//записывает фукцию в слот
{
	if (PSLOTS > slot){
		AppPtr[slot].app = _app;
		AppPtr[slot].period = _app->GetUpdatePeriod();
	}
}

void MTask::HwStop()//Останавливает работу диспетчера
{
	TCCR5B &= ~((1<<CS51) | (1<<CS50));//прескалер на 64.
	TIMSK5 &= ~(1<<TOIE5);
}

uint32_t MTask::millis(){
	unsigned long m;
	uint8_t oldSREG = SREG;
	cli();
	m = Millis;
	SREG = oldSREG;
	return m;
	
}

void MTask::Search(){
	Millis++;
	for (uint8_t slot = 0; slot < PSLOTS; slot++)
	{//смотрим, подошло ли время:
		if (AppPtr[slot].app != 0){//Check app pointer
			if(AppPtr[slot].period != 0){//Check update time
				AppPtr[slot].period--;//Count to zero
				if(AppPtr[slot].period == 0){//if there is zero now
					AppPtr[slot].period = AppPtr[slot].app->HwClock(Millis);//call HwClock and update period
				}
			}
		}
	} 
}


ISR(TIMER5_OVF_vect) {
	TCNT5 = TIMETICK;//update tick
	Task.Search();
 }  


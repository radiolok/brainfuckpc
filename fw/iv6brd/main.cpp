/*
 * iv6brd.cpp
 *
 * Created: 14.12.2017 22:57:47
 * Author : radiolok
 */ 

#include <avr/io.h>

#define F_CPU 1000000
#include "MTask.h"
#include "SegmentDisplay.h"

static uint32_t SCHEDULER_PERIOD = 10;//ms

	static uint16_t data = 0;
	uint8_t state = 0;
void Incrementer()
{
	DDRC |= (1 << PC5);
	if (state)
	{
		state = 0;
		PORTC &= ~(1<<PC5);
	}
	else {
		state = 1;
		PORTC |= (1 << PC5);
	}
	SegmentDisplay::Instance()(data, 0, 0);
	data++;
}

int main(void)
{
	MTask::Instance().Init(SCHEDULER_PERIOD, F_CPU);
	SegmentDisplay::Instance().Init(6, 0x0F);
	MTask::Instance().Add(Incrementer, 0, 10);
    /* Replace with your application code */
	MTask::Instance().Start();
}


/*
 * iv6brd.cpp
 *
 * Created: 14.12.2017 22:57:47
 * Author : radiolok
 */ 

#include <avr/io.h>

#define F_CPU 8000000
#define BAUD_RATE 19200
#include "MTask.h"
#include "log.h"
#include "uart.h"
#include "SegmentDisplay.h"

static uint32_t SCHEDULER_PERIOD = 1;//ms

	static uint16_t data = 0;

void Incrementer()
{
	static uint8_t state = 0;
	DDRC |= (1 << PC4);
	if (state)
	{
		state = 0;
		PORTC &= ~(1<<PC4);
	}
	else {
		state = 1;
		PORTC |= (1 << PC4);
	}
	//data = 0xDCBA;
	SegmentDisplay::Instance()(data, 0, 0);
	data++;
}

int main(void)
{
	sei();
	uart_init(UART_BAUD_SELECT(BAUD_RATE, F_CPU));
	log_trace("uart started");
	MTask::Instance().Init(SCHEDULER_PERIOD, F_CPU);
	log_trace("MTask Inited");
	SegmentDisplay::Instance().Init(6, 0x10);
	log_trace("Segment display init");
	MTask::Instance().Add(Incrementer, 0, 10);
	log_trace("Data changer inited");
    /* Replace with your application code */
	MTask::Instance().Start();
}


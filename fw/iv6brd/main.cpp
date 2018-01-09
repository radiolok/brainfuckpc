/*
 * iv6brd.cpp
 *
 * Created: 14.12.2017 22:57:47
 * Author : radiolok
 */ 

#include <avr/io.h>

#define F_CPU 1000000
#include "MTask.h"

static uint32_t SCHEDULER_PERIOD = 10;//ms


int main(void)
{
	MTaskSingleton::Instance().Setup(SCHEDULER_PERIOD, F_CPU);
    /* Replace with your application code */
    while (1) 
    {
    }
}


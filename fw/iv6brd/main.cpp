/*
 * iv6brd.cpp
 *
 * Created: 14.12.2017 22:57:47
 * Author : radiolok
 */ 

#include <avr/io.h>

#include "menuos/MTask.h"

static uint32_t SCHEDULER_PERIOD = 10;//ms
static uint32_t CPU_FREQUENCY = 1000000;//TODO: check fuses

MTask mTask(SCHEDULER_PERIOD, CPU_FREQUENCY);

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}


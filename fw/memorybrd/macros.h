/*
 * macros.h
 *
 * Created: 29.05.2017 22:54:33
 *  Author: radiolok
 */ 


#ifndef MACROS_H_
#define MACROS_H_


#include <avr/io.h>
#include "util/memoryport.h"
#include "log.h"

#define F_CPU 16000000UL
#include <util/delay.h>
#define BAUD_RATE 38400

#define NULL 0

#define low(x)   ((x) & 0xFF)
#define high(x)   (((x)>>8) & 0xFF)

#define HIGH true
#define LOW false



#endif /* MACROS_H_ */
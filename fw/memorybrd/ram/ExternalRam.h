/* 
* ExternalRam.h
*
* Created: 29.05.2017 22:42:28
* Author: radiolok
*/


#ifndef __EXTERNALRAM_H__
#define __EXTERNALRAM_H__

#include "../macros.h"

void inline ramSetAddress(uint16_t addr)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	PORTA = low(addr);
	dbg_trace_val("ramSetAddress = low:", PINA);
	PORTC = high(addr);
	dbg_trace_val("ramSetAddress = high:", PINC);
}

void inline ramSetOE()
{
	dbg_trace("ramSetOE");
	PORTE |= (1 << PE2);
}

void inline ramReleaseOE()
{
	dbg_trace("ramReleaseOE");
	PORTE &= ~(1 << PE2);
}

void inline ramSetRead()
{
	dbg_trace("ramSetRead");
	PORTE &= ~(1 << PE3);
	DDRF = 0x00;
	DDRK = 0x00;
	PORTK = 0xFF;
	PORTF = 0xFF;
}

void inline ramSetWrite()
{
	dbg_trace("ramSetWrite");
	PORTE |= (1 << PE3);
	DDRF = 0xFF;
	DDRK = 0xFF;
}

void inline ramReleaseLine(void)
{
	ramReleaseOE();
	ramSetRead();
	DDRA = 0x00;
	DDRC = 0x00;
	DDRK = 0x00;
	DDRF = 0x00;
	PORTA = 0x00;
	PORTC = 0x00;
	PORTK = 0x00;
	PORTF = 0x00;
}


void inline ramSetData(uint16_t data)
{
		PORTF = low(data);
		dbg_trace_val("ramSetData = low:", PINF);
		PORTK = high(data);
		dbg_trace_val("ramSetData = high:", PINK);
}

uint16_t inline ramGetData(void)
{
	dbg_trace_val("ramGetData = low:", PINF);
	dbg_trace_val("ramGetData = high:", PINK);
	return (PINK << 8) + PINF;
}

uint8_t ramInit();

uint16_t ramReadWord(uint16_t addr);

void ramWriteWord(uint16_t addr, uint16_t data);

uint16_t ramReadFromBus(uint16_t addr);

uint16_t ramWriteToBus(uint16_t addr);

void ramLock();

void ramUnlock();

uint8_t ramCheckLock();

#endif //__EXTERNALRAM_H__

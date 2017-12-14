/* 
* ExternalRam.h
*
* Created: 29.05.2017 22:42:28
* Author: radiolok
*/


#ifndef __EXTERNALRAM_H__
#define __EXTERNALRAM_H__

#include "util/macros.h"

void inline ramSetAddress(uint16_t addr)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	PORTA = low(addr);
	PORTC = high(addr);
}

void inline ramSetOE()
{
	PORTE |= (1 << PE2);
}

void inline ramReleaseOE()
{
	PORTE &= ~(1 << PE2);
}

void inline ramSetRead()
{
	PORTE |= (1 << PE3);
}

void inline ramSetWrite()
{
	PORTE &= ~(1 << PE3);
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
		DDRF = 0xFF;
		DDRK = 0xFF;
		PORTF = low(data);
		PORTK = high(data);
}

uint16_t inline ramGetData(void)
{
	DDRF = 0x00;
	DDRK = 0x00;
	return (PORTK << 8) + PORTF;
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

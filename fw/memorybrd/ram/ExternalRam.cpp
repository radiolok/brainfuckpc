/* 
* ExternalRam.cpp
*
* Created: 29.05.2017 22:42:28
* Author: radiolok
*/


#include "ExternalRam.h"

uint8_t ramLockAccess = 0;

uint8_t ramInit(void)
{
	DDRE |= (1 << PE2) | (1 << PE3);
	PORTE &= ~((1 << PE2) | (1 << PE3));
	return 0;
}

uint16_t ramReadWord(uint16_t addr)
{
	uint16_t result = 0;
	if (!ramCheckLock())
	{
		ramSetAddress(addr);
		ramSetOE();
		_delay_us(2);
		result = ramGetData();
		_delay_us(2);
		ramReleaseOE();
	}
	ramReleaseLine();		
	return result;
}

void ramWriteWord(uint16_t addr, uint16_t data)
{
	if (!ramCheckLock())
	{
		ramSetAddress(addr);
		ramSetData(data);
		ramSetWrite();
		_delay_us(2);
		ramSetRead();
	}
	ramReleaseLine();
}

uint16_t ramReadFromBus(uint16_t addr)
{
	uint16_t result;
	
	return result;
}

uint16_t ramWriteToBus(uint16_t addr)
{
	uint16_t result;

	return result;
}

void ramLock(void)
{
	ramLockAccess = 1;
}

void ramUnlock(void)
{
	ramLockAccess = 0;
}

uint8_t ramCheckLock(void)
{
	return ramLockAccess;
}
/* 
* ExternalRam.cpp
*
* Created: 29.05.2017 22:42:28
* Author: radiolok
*/


#include "ExternalRam.h"

uint8_t ramLockAccess = 0;


last_tsx_t lastTsx;

uint16_t ramLastData()
{
	return lastTsx.lastData;
}

uint16_t ramLastAddress()
{
	return lastTsx.lastAddr;
}

uint8_t ramLastTsx()
{
	return lastTsx.type;
}

uint8_t ramInit(void)
{

	DDRE |= (1 << PE2) | (1 << PE3);
	PORTE |= ((1 << PE2) | (1 << PE3));
	DDRG |= (1 << PG1);
	
	DDRJ |= (1<< PJ4);//CS
	PORTJ &= ~(1 << PJ4);
	lastTsx.lastAddr = 0x00;
	lastTsx.lastData = 0x00;
	lastTsx.type = RAM_READ;
	//INT init:
	
	EICRB |= (1 << ISC40);
	EIMSK |= (1 << INT4);
	log_trace("ramInit Done");
	return 0;
}

int16_t ramWriteWordBuffer(uint16_t start_addr, const uint16_t *data, uint16_t length)
{
	int16_t result = 0;
	uint16_t end_addr = start_addr + length;
	uint16_t addr = start_addr;
	while(addr != end_addr)
	{
		result += ramWriteWord(addr++, *(data++));
	}
	return result;
}

int16_t ramReadWordBuffer(uint16_t start_addr, uint16_t *data, uint16_t length)
{
	int16_t result = 0;
	uint16_t end_addr = start_addr + length;
	uint16_t addr = start_addr;
	while(addr != end_addr)
	{
		result += ramReadWord(addr++, data++);
	}
	return result;
}



int16_t ramReadWord(uint16_t addr, uint16_t *data)
{
	int16_t result = -1;
	if (!ramCheckLock())
	{
		ramSetMcuAddrPortWrite();
		ramSetAddress(addr);
		ramSetCs();
		ramSetOE();
		_delay_us(2);
		*data = ramGetData();
		_delay_us(2);
		ramClrCs();
		ramReleaseOE();
		result = 0;
	}
	ramReleaseLine();		
	return result;
}

int16_t ramWriteWord(uint16_t addr, uint16_t data)
{
	int16_t result = -1;
	if (!ramCheckLock())
	{
		ramSetMcuAddrPortWrite();
		ramSetMcuDataPortWrite();
		ramSetAddress(addr);
		ramSetData(data);
		ramSetWrite();
		ramSetCs();
		_delay_us(2);
		ramClrCs();
		ramSetRead();
		result = 0;
	}
	ramReleaseLine();
	return result;
}

int16_t ramDataToBus(uint16_t addr)
{
	int16_t result = -1;
	if (!ramCheckLock())
	{
		ramSetMcuAddrPortWrite();
		ramSetAddress(addr);
		ramSetOE();
		ramSetCs();
		result = 0;
	}
	return result;
}

int16_t ramDataFromBus(uint16_t addr)
{
	int16_t result = -1;
	if (!ramCheckLock())
	{
		ramSetMcuAddrPortWrite();
		ramSetAddress(addr);
		ramSetWrite();
		ramSetCs();
		_delay_us(2);
		result = 0;
	}
	return result;
}

void ramLock(void)
{
	ramLockAccess = 1;
	ramReleaseLine();
}

void ramUnlock(void)
{
	ramLockAccess = 0;
}

uint8_t ramCheckLock(void)
{
	//dbg_trace_val("RamLock=",ramLockAccess);
	return ramLockAccess;
}







ISR(INT4_vect)
{
	//have sync!
	if ((PINE >> PE4) & 0x01)
	{
		//Sync started!
		ramLock();
		lastTsx.lastAddr = ramGetAddress();
		lastTsx.lastData = ramGetData();
		if ((PINE >> PE5) & 0x01)
		{
			lastTsx.type = RAM_WRITE;
		}
		else
		{
			lastTsx.type = RAM_READ;
		}
	}
	else
	{
		//Sync ended!
		ramUnlock();
	}
}
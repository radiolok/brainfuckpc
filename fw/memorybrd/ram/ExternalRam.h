/* 
* ExternalRam.h
*
* Created: 29.05.2017 22:42:28
* Author: radiolok
*/


#ifndef __EXTERNALRAM_H__
#define __EXTERNALRAM_H__

#include "../macros.h"
//#include "../driver/dataIO.h"
#include <avr/interrupt.h>

enum type
{
	RAM_READ,
	RAM_WRITE,
	RAM_COUT,
	RAM_CIN
};

typedef struct _last_tsx_t
{
	uint16_t data = 0;
	uint16_t addr = 0;
	uint8_t type = RAM_READ;
	
}last_tsx_t;

int8_t ramEventGet(last_tsx_t *event);


int16_t ramWriteWordBuffer(uint16_t start_addr, const uint16_t *data, uint16_t length);

int16_t ramReadWordBuffer(uint16_t start_addr, uint16_t *data, uint16_t length);

void inline ramSetAddress(uint16_t addr)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	PORTA = low(addr);
	//dbg_trace_val("ramSetAddress = low:", PINA);
	PORTC = high(addr);
	//dbg_trace_val("ramSetAddress = high:", PINC);
}

uint16_t inline ramGetAddress()
{
	return (PINC << 8) + PINA;
}

void inline ramSetOE()
{
	//dbg_trace("ramSetOE");
	PORTE |= (1 << PE2);
}

void inline ramReleaseOE()
{
	//dbg_trace("ramReleaseOE");
	PORTE &= ~(1 << PE2);
}

void inline ramSetMcuDataPortWrite()
{
	DDRF = 0xFF;
	DDRK = 0xFF;
}

void inline ramSetMcuDataPortRead()
{
	//TODO: Add CS line - we have Two ports in Output mode here.
	DDRF = 0x00;
	DDRK = 0x00;
	PORTK = 0x00;
	PORTF = 0x00;
}

void inline ramSetMcuAddrPortWrite()
{
	DDRA = 0xFF;
	DDRC = 0xFF;
}

void inline ramSetMcuAddrPortRead()
{
	//TODO: Add CS line - we have Two ports in Output mode here.
	DDRA = 0x00;
	DDRC = 0x00;
	PORTA = 0x00;
	PORTC = 0x00;
}

void inline ramSetRead()
{
	//dbg_trace("ramSetRead");
	PORTE &= ~(1 << PE3);
}



void inline ramSetWrite()
{
	//dbg_trace("ramSetWrite");
	PORTE |= (1 << PE3);
}

void inline ramSetCs()
{
	//dbg_trace("ramSetCs");
	PORTJ |= (1 << PJ4);
}



void inline ramClrCs()
{
	//dbg_trace("ramClrCs");
	PORTJ &= ~(1 << PJ4);
}

void inline ramReleaseLine(void)
{
	ramReleaseOE();
	ramClrCs();
	ramSetRead();
	ramSetMcuAddrPortRead();
	ramSetMcuDataPortRead();
}


void inline ramSetData(uint16_t data)
{
		PORTF = low(data);
		//dbg_trace_val("ramSetData = low:", PINF);
		PORTK = high(data);
		//dbg_trace_val("ramSetData = high:", PINK);
}

uint16_t inline ramGetData(void)
{
	return (PINK << 8) + PINF;
}

uint8_t ramInit();

int16_t ramReadWord(uint16_t addr, uint16_t *data);

int16_t ramWriteWord(uint16_t addr, uint16_t data);

int16_t ramDataFromBus(uint16_t addr);

int16_t ramDataToBus(uint16_t addr);

void ramLock();

void ramUnlock();

uint8_t ramCheckLock();

uint16_t ramLastData();
uint16_t ramLastAddress();
uint8_t ramLastTsx();

#endif //__EXTERNALRAM_H__

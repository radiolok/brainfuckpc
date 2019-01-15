/* 
* STP16CP05.cpp
*
* Created: 15.01.2019 20:26:19
* Author: radiolok
*/


#include "STP16CP05.h"

void STP16CP05_SetColumn(uint8_t column)
{
	if (column < 16)
	{	
		uint16_t column_run = (1U << column);
		//STP16CP05_Blank(true);
		//_delay_us(2);
		//STP16CP05_Blank(false);
		spi_sendByte(high(column_run));
		spi_sendByte(low(column_run));
		spi_sendByte(high(column_run));
		spi_sendByte(low(column_run));
		STP16CP05_Latch();
		
	}
}


void STP16CP05_Init()
{
	spi_init();
	DDRB |= (1<< PB4);
	STP16CP05_Blank(false);
	
	DDRJ |= (1 << PJ3);
	dbg_trace("STP16CP05 Init");
}

void STP16CP05_Blank(uint8_t mode)
{
	if (mode == true)
	{
		PORTB |= (1 << PB4);
	}
	else
	{
		PORTB &= ~ (1 << PB4);
	}
}

void STP16CP05_Latch()
{
	PORTJ |= (1 << PJ3);
	_delay_us(2);
	PORTJ &= ~(1 << PJ3);
}

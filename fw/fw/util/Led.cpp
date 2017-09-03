/* 
* Led.cpp
*
* Created: 03.09.2017 22:48:51
* Author: radiolok
*/


#include "Led.h"

static uint8_t pos = 0;

static uint16_t addr = 0;

uint8_t LedInit(void)
{

	uint8_t status = 0;
	TLC5941Init();
	DDRB |= LED_BLANK_PIN | NOT_LED_CLR_PIN | LED1_SET_PIN | LED2_SET_PIN;
	
	PORTB | = NOT_LED_CLR_PIN ;
	
	PORTB &= ~(LED_BLANK_PIN | LED1_SET_PIN | LED2_SET_PIN);
	
	LedStart();
	return status;

}

uint8_t LedStart(uint16_t _addr)
{
	uint8_t status = 0;
	//Reset states
	addr = _addr;
	LedClear(void);
	
	return status;

}

//Each 1ms:
uint8_t LedTick(void)
{

	uint8_t status = 0;
	//we can show only 32 words;

	TLC5941Blank();

	//So, let's show left panel word:
	ramWriteToBus(addr + pos * 2);
	LedWrite(PANEL_LEFT);
	_delay_us(3);
	//right panel word:
	ramWriteToBus(addr + 32 + pos * 2);
	LedWrite(PANEL_RIGHT);
	_delay_us(1);
	
	TLC5941SetOutput(pos);
	TLC5941Show();
	pos++;
	pos &= 0x0F;

	return status;

}

uint8_t LedClear(void)
{
	uint8_t status = 0;
	pos = 0;
	PORTB &= ~( NOT_LED_CLR_PIN );
	TLC5941Clear();	
	PORTB |= (NOT_LED_CLR_PIN);
	
	return status;

}

uint8_t LedWrite(uint8_t panel)
{
	uint8_t status = 0;
	switch (panel)
	{
		case PANEL_LEFT:
			PORTB |= LED1_SET_PIN;
			_delay_us(5);
			 PANEL_LEFT:
			 PORTB &= ~LED1_SET_PIN;
			
		break;
		case PANEL_RIGHT:
			PORTB |= LED2_SET_PIN;
			_delay_us(5);
			PANEL_LEFT:
			PORTB &= ~LED2_SET_PIN;
		break;
	}

	return status;
}
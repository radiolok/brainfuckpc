/*Copyright (c) 2013-2017, Artem Kashkanov
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted 
provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of 
conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other materials 
provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/



#include "pinIO.h"

uint8_t getInputPin(uint8_t pinNumber)
{
	uint8_t result = 0;
	switch (pinNumber)
	{
		case (uint8_t)PinExtIn.I1:
			result = (PINH >> PH4) & 0x01;	
		break;
		case (uint8_t)PinExtIn.I2:
			result = (PINH >> PH3) & 0x01;	
		break;
		case (uint8_t)PinExtIn.I3:
			result = (PINH >> PH2) & 0x01;		
		break;
		case (uint8_t)PinExtIn.I4:
			result = (PINE >> PE7) & 0x01;				
		break;
		case (uint8_t)PinExtIn.I5:
			result = (PINE >> PE6) & 0x01;					
		break;
		case (uint8_t)PinExtIn.I6:
			result = (PINJ >> PJ6) & 0x01;							
		break;
		case (uint8_t)PinExtIn.I7:
			result = (PINJ >> PJ5) & 0x01;									
		break;
		case (uint8_t)PinExtIn.I8:
			result = (PINJ >> PJ4) & 0x01;											
		break;
		case (uint8_t)PinExtIn.I9:
			result = (PINJ >> PJ3) & 0x01;													
		break;
		case (uint8_t)PinExtIn.STDIN_MODE:
			result = (PINH >> PH6) & 0x01;															
		break;
		case (uint8_t)PinExtIn.STDIN_RD:
			result = (PINH >> PH5) & 0x01;																		
		break;
		case (uint8_t)PinExtIn.STDOUT_WR:
			result = (PINH >> PH7) & 0x01;																				
		break;
		case (uint8_t)PinExtIn.Sync:
			result = (PINE >> PE4) & 0x01;																					
		break;
		case (uint8_t)PinExtIn.WORD_BIT_MODE:
		result = (PING >> PG5) & 0x01;
		break;
		case (uint8_t)PinExtIn.WR:
			result = (PINE >> PE5) & 0x01;																							
		break;
		case (uint8_t)PinExtIn.DO_NOT_CONNECT_1:
			result = (PINB >> PB0) & 0x01;																									
		break;
		default:
			result = 0;
		break;	
	}
	return result;
}

void SetOutputPin(uint8_t pinNumber, uint8_t state)
{
	switch (pinNumber)
	{
		case (uint8_t)PinExtOut.IO0:
			DDRG  |= (1 << PG1);
			if (state) {PORTG |= (1 << PG1);} else {PORTG &= ~(1<<PG1);}
		break;
		case (uint8_t)PinExtOut.IO1:
			DDRG  |= (1 << PG0);
			if (state) {PORTG |= (1 << PG0);} else {PORTG &= ~(1<<PG0);}
		break;
		case (uint8_t)PinExtOut.IO2:
			DDRD  |= (1 << PD7);
			if (state) {PORTG |= (1 << PD7);} else {PORTG &= ~(1<<PD7);}
		break;
		case (uint8_t)PinExtOut.IO3:
			DDRD  |= (1 << PD6);
			if (state) {PORTG |= (1 << PD6);} else {PORTG &= ~(1<<PD6);}
		break;
		case (uint8_t)PinExtOut.IO4:
			DDRD  |= (1 << PD5);
			if (state) {PORTG |= (1 << PD5);} else {PORTG &= ~(1<<PD5);}
		break;
			DDRD  |= (1 << PD4);
			if (state) {PORTG |= (1 << PD4);} else {PORTG &= ~(1<<PD4);}
		break;
		case (uint8_t)PinExtOut.IO6:
			DDRD  |= (1 << PD3);
			if (state) {PORTG |= (1 << PD3);} else {PORTG &= ~(1<<PD3);}
		break;
		case (uint8_t)PinExtOut.IO7:
			DDRD  |= (1 << PD2);
			if (state) {PORTG |= (1 << PD2);} else {PORTG &= ~(1<<PD2);}
		break;
		case (uint8_t)PinExtOut.IO8:
			DDRL  |= (1 << PL7);
			if (state) {PORTG |= (1 << PL7);} else {PORTG &= ~(1<<PL7);}
		break;
		case (uint8_t)PinExtOut.IO9:
			DDRL  |= (1 << PL6);
			if (state) {PORTG |= (1 << PL6);} else {PORTG &= ~(1<<PL6);}
		break;
		case (uint8_t)PinExtOut.IO10:
			DDRL  |= (1 << PL5);
			if (state) {PORTG |= (1 << PL5);} else {PORTG &= ~(1<<PL5);}
		break;
		case (uint8_t)PinExtOut.IO11:
			DDRL  |= (1 << PL4);
			if (state) {PORTG |= (1 << PL4);} else {PORTG &= ~(1<<PL4);}
		break;
		case (uint8_t)PinExtOut.IO12:
			DDRL  |= (1 << PL3);
			if (state) {PORTG |= (1 << PL3);} else {PORTG &= ~(1<<PL3);}
		break;
		case (uint8_t)PinExtOut.IO13:
			DDRL  |= (1 << PL2);
			if (state) {PORTG |= (1 << PL2);} else {PORTG &= ~(1<<PL2);}
		break;
		case (uint8_t)PinExtOut.IO14:
			DDRL  |= (1 << PL1);
			if (state) {PORTG |= (1 << PL1);} else {PORTG &= ~(1<<PL1);}
		break;
		case (uint8_t)PinExtOut.IO15:
			DDRL  |= (1 << PL0);
			if (state) {PORTG |= (1 << PL0);} else {PORTG &= ~(1<<PL0);}
		break;
		default:

		break;
	}
}
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


#ifndef __TLC5941_H__
#define __TLC5941_H__

#include "../macros.h"
#include <string.h>
#include "spi.h"

void TLC5941Init(void);

void TLC5941SetCurrent(uint8_t current);

void TLC5941SetColumn(uint8_t column);

inline void TLC5941SetBlank(void)
{
	PORTB |= (1 << PB4);
}

inline void TLC5941ReleaseBlank(void)
{
	PORTB &= ~(1 << PB4);
}

inline void TLC5941Update(void)
{
	//XLAT
	PORTJ |= (1 << PJ3);
	_delay_us(2);
	PORTJ &= ~(1 << PJ3);
}

inline void TLC5941Pulse(void)
{
	//XLAT
	PORTB |= (1 << PB1);
	_delay_us(2);
	PORTB &= ~(1 << PB1);
}

inline void TLC5941Data(uint8_t state)
{
	if (state)
	{
	PORTB |= (1 << PB2);	
	}
	else
	{
	PORTB &= ~(1 << PB2);	
	}
}

class TLC5941 {
	public:
	
	/* Channel sizes and counts: */
	#define TLC5941_COUNT 1
	#define GS_CHANNEL_LEN 12 /* Each GS channel is 12 bits */
	#define DC_CHANNEL_LEN 6 /* Each DC channel is 6 bits */
	#define GS_SIZE 192 /* Total size in bits of Grayscale PWM control */
	#define DC_SIZE 96 /* Total size in bits of Dot Correction */
	
	/* Convenience macros: */
	//#define outputState(port, pin) ((port) & (1 << (pin))) /* Reads state of pin */
	//#define PULSE(pin) { digitalWrite(pin, HIGH); digitalWrite(pin, LOW); } /* Send a pulse to a pin */
	//#define SET_BLANK(blank) digitalWrite(BLANK, blank);
	//#define SET_MODE(md) do {if (md)} while(0);
	
	
		
	void SET_MODE(uint8_t md)
	{
		/*if (MD == MD_DC)
		{
			PORTB |= (1 << PB4);
		}
		else{
			PORTB &= ~(1 << PB4);
		}*/
	}
	void SET_BLANK(uint8_t blank)
	{
		if (blank)
		{
			PORTB |= (1 << PB4);
		}
		else{
			PORTB &= ~(1 << PB4);
		}
	}

	/* Pin definitions: */
	enum TLCPINS {
		SIN,      /* Serial input */
		SCLK,     /* Serial clock */
		XLAT,     /* Serial data latch into the registers */
		BLANK,    /* Turns off LEDS and signals the start of the Grayscale cycle */
		MODE,     /* 0 = In Dot Correction Mode | 1 = In Grayscale Mode */
		XERR      /* XERR signals LED overheating */
	};

	/* Modes: */
	enum MD {
		MD_GS, /* Grayscale mode */
		MD_DC  /* Dot Correction Mode */
	};
	
	TLC5941() {}

	void init(void) {
		
		//spi_init();
		DDRB |= (1<< PB4) | (1 << PB2) | (1 << PB1);
		DDRJ |= (1 << PJ3);
		
		SET_MODE(MD_DC);
		SET_BLANK(HIGH);

		/* Send default dot correction data: */
		sendDot();
	}

	

	/* Sets dot correction value (from 0 to 64) for a certain channel */
	inline void setDot(uint8_t channel, uint8_t dot_val) {
		int startOff = DC_SIZE - (channel * DC_CHANNEL_LEN) - DC_CHANNEL_LEN;
		uint8_t * new_dc_dat = byte_to_binary(dot_val, DC_CHANNEL_LEN);
		memcpy(gsData + startOff, new_dc_dat, DC_CHANNEL_LEN);
	}

	/* Sets brightness value (from 0 to 4096) for a certain channel */
	inline void setChannel(uint8_t channel, uint16_t brightness) {
		int startOff = GS_SIZE - (channel * GS_CHANNEL_LEN) - GS_CHANNEL_LEN;
		uint8_t * new_gs_dat = byte_to_binary(brightness, GS_CHANNEL_LEN);
		memcpy(gsData + startOff, new_gs_dat, GS_CHANNEL_LEN);
	}

	/* Updates the chip by outputting the DC and GS data */
	inline void update() {
		sendDot();
		sendGS();
	}
	
	private:
	/* There is no need for hardcoding all the 1's and 0's here. This is here for reference purpose */

	/* Dot correction data: */
	uint8_t dcData[TLC5941_COUNT * DC_SIZE] = {
		// MSB         LSB
		1, 1, 1, 1, 1, 1,  // Channel 15
		1, 1, 1, 1, 1, 1,  // Channel 14
		1, 1, 1, 1, 1, 1,  // Channel 13
		1, 1, 1, 1, 1, 1,  // Channel 12
		1, 1, 1, 1, 1, 1,  // Channel 11
		1, 1, 1, 1, 1, 1,  // Channel 10
		1, 1, 1, 1, 1, 1,  // Channel 9
		1, 1, 1, 1, 1, 1,  // Channel 8
		1, 1, 1, 1, 1, 1,  // Channel 7
		1, 1, 1, 1, 1, 1,  // Channel 6
		1, 1, 1, 1, 1, 1,  // Channel 5
		1, 1, 1, 1, 1, 1,  // Channel 4
		1, 1, 1, 1, 1, 1,  // Channel 3
		1, 1, 1, 1, 1, 1,  // Channel 2
		1, 1, 1, 1, 1, 1,  // Channel 1
		1, 1, 1, 1, 1, 1,  // Channel 0
	};
	
	/* Grayscale data */
	uint8_t gsData[TLC5941_COUNT * GS_SIZE] = {
		// MSB                           LSB
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 15
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 14
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 13
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 12
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 11
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 10
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 8
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 7
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 6
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 5
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 4
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 3
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 2
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 1
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Channel 0
	};

	/* Send dot correction data: */
	inline void sendDot(void) {
		SET_MODE(MD_DC);
		
		for(uint8_t ctr = 0;;) {
			if(ctr > TLC5941_COUNT * DC_SIZE - 1) {
				TLC5941Update();
				break;
				} else {
				TLC5941Data(dcData[ctr++]);
				
				TLC5941Pulse();
			}
		}
	}

	/* Send grayscale data: */
	inline void sendGS(void) {
		//uint8_t first_cycle_fl = 0;
		uint8_t data_ctr = 0;
/*
		if(outputState(PORTD, MODE)) {
			SET_MODE(MD_GS);
			first_cycle_fl = 1;
		}*/
		
		SET_BLANK(LOW);
		for(uint16_t gsclk_ctr = 0; gsclk_ctr <= 4095; gsclk_ctr++)
		if(!(data_ctr > TLC5941_COUNT * GS_SIZE - 1)) {
			TLC5941Data(gsData[data_ctr++]);
			
			TLC5941Pulse();
		}

		/* End of GS cycle */
		SET_BLANK(HIGH);
		TLC5941Update();
		//if(first_cycle_fl)
		//PULSE(SCLK);
	}
	
	inline uint8_t * byte_to_binary(int x, int bitcount) {
		static uint8_t b[GS_CHANNEL_LEN]; /* I picked the biggest channel */
		for (int z = (1 << bitcount), i = 0; z > 0; z >>= 1)
		b[i++] = (x & z) == z;
		return b;
	}
};



#endif //__TLC5941_H__

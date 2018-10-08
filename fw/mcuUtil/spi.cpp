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
#include "spi.h"

#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	#define MEMORYBRD
#else
	#define IV6_BRD
#endif


#if defined(IV6_BRD)
	//#error "Not a memory board!"
#endif

void spi_init()
{
	
	#if defined(MEMORYBRD)
		//dbg_trace("spi_init_memorybrd");
		DDRB |= (1<< PB0) |(1<< PB1) | (1<< PB2);//SCK MOSI SS!
		SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
	#else
		//dbg_trace("spi_init_iv6_brd");
		DDRB &= ~(1<< PB4);//MISO
		DDRB |= (1<< PB5);//SCK
		SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
	#endif
} 



uint8_t spiTxBuffer[SPI_TX_BUFFER];
uint8_t spiTxGet = 0;
uint8_t spiTxSend = 0;

void spi_close()
{
	SPCR = 0x00;
}


uint8_t spi_sendByte(uint8_t data)
{
	//spiTxBuffer[spiTxGet] = data;
	//spiTxGet = (spiTxGet + 1) & SPI_TX_BUFFER_MASK;
	//dbg_trace_val("spiSendByte", data);
	spi_init();
	uint8_t result = 0;
	//wait transmission done
	 SPDR = data;
	 while(!(SPSR & (1 << SPIF)));
	 result = SPDR;
	 spi_close();
	 return result;
}

/*
ISR(SPI_STC_vect)
{


}*/
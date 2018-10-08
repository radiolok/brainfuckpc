/* 
* midi.cpp
*
* Created: 22.09.2018 22:01:51
* Author: radiolok
*/


#include "midi.h"

uint32_t notes[]
{
	1956947,//C
	1847042,//C#
	1743489,//D
	1646090,//D#
	1553247,//E
	1466074,//F
	1384083,//F#
	1306122,//G
	1233141,//G#
	1163636,//A
	1098524,//A#
	1036672//B
};

uint16_t getNotePeriod(uint16_t note, uint8_t *delim)
{
	uint16_t octave = note / 12;
	uint32_t FullPeriod = (notes[note % 12] >> (octave));

	if (delim != NULL)
	{
		*delim = (octave < 2) ? 64 : 8;
		return static_cast<uint16_t>(FullPeriod >> ((octave < 2)? 6 : 3));
	}
	return 0;
}

volatile uint8_t currentPin = (uint8_t)PinExtOut::IO11;

void setupTimer(void)
{
	currentPin = (uint8_t)PinExtOut::IO11;
	TCCR5A = (1<< COM5B1) | (1 << COM5B0) | (1 << WGM51) | (1 << WGM50);
	TCCR5B = (1 << WGM53) | (1 << WGM52);
	TIMSK5 = (1<< TOIE5);
}

void noteOn(uint16_t note)
{
	if (note == 0)
	{
		log_trace("noteOn = 0");
		noteOff();
		return;
	}
	uint8_t delim = 0;
	uint16_t period = getNotePeriod(note, &delim);
	TCCR5A &= ~((1<< COM5C1) | (1 << COM5C0));
	TCCR5A |= ((1<< COM5B1) | (1 << COM5B0));
	currentPin = (uint8_t)PinExtOut::IO11;
	OCR5A = period;
	OCR5B = period >> 1;
	OCR5C = period >> 1;
	TCNT5 = 0x00;
	TCCR5B |= (delim == 64)? 3 : 2;
	TIMSK5 |= (1<< TOIE5);
	log_trace_val("noteOn = ", note);
}
void noteOff()
{
	TCCR5B &= ~(0x07);
	TIMSK5 &= ~(1 << TOIE5);
	SetOutputPin((uint8_t)PinExtOut::IO11, LOW);
	SetOutputPin((uint8_t)PinExtOut::IO10, LOW);
	log_trace("noteOff");
}


ISR(TIMER5_OVF_vect){
	if (currentPin == (uint8_t)PinExtOut::IO11)
	{
		TCCR5A &= ~((1<< COM5B1) | (1 << COM5B0));	
		TCCR5A |= ((1<< COM5C1) | (1 << COM5C0));	
		currentPin = (uint8_t)PinExtOut::IO10;
	}
	else
	{
		TCCR5A &= ~((1<< COM5C1) | (1 << COM5C0));
		TCCR5A |= ((1<< COM5B1) | (1 << COM5B0));
		currentPin = (uint8_t)PinExtOut::IO11;
	}
}

int startMidi(void)
{
	uart_init(UART_BAUD_SELECT(BAUD_RATE, F_CPU));
	uart2_init(UART_BAUD_SELECT(31250, F_CPU));

	setupTimer();

	uint8_t note_packet[3] = {0,0};
	uint8_t waitForBytes = 0;
	uint8_t currentNote = 0;
	while (1)
	{
		if (uart2_available() > 0)
		{
			uint8_t data = uart2_getc();
			//if ((data != 0xfe) || (data != 0xf8))
			//uart_print(data, 16);
			if (data & 0x80)
			{
				switch (data & 0xF0)
				{
					case 0x80://Note Off event
						uart_print(data, 16);
						note_packet[0] = data;
						waitForBytes = 2;
					break;
					case 0x90://Note On event
						uart_print(data, 16);
						note_packet[0] = data;
						waitForBytes = 2;
					break;
					case 0xF0:
					//system real-time:
					if (data == 0xFC)
					{
						noteOff();
					}
					break;
				}
			}
			else
			{
				if (waitForBytes)
				{

					note_packet[3 - waitForBytes] = data;
					waitForBytes--;
				}
				if (!waitForBytes)
				{
					if (note_packet[2] > 0)
					{
						noteOn(note_packet[1]);
						currentNote = note_packet[1];
					}

					else
					{
						if (currentNote == note_packet[1])
						noteOff();
					}
					waitForBytes = 2;
				}
			}
		}

		if (uart_available() > 0)
		{
			uint8_t note = uart_getc();
			if (note == 0x20)
			{
				noteOff();
			}
			else{
				noteOn(note);
			}
			uart_putc(note);
		}

	}
}
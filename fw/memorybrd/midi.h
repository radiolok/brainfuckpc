/* 
* midi.h
*
* Created: 22.09.2018 22:01:51
* Author: radiolok
*/


#ifndef __MIDI_H__
#define __MIDI_H__

#include "macros.h"
#include <avr/interrupt.h>
#include "driver/pinIO.h"
#include "uart.h"


uint16_t getNotePeriod(uint16_t note, uint8_t *delim);

void setupTimer(void);

void noteOn(uint16_t note);

void noteOff();

int startMidi();

#endif //__MIDI_H__

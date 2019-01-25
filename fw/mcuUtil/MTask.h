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


#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include <avr/interrupt.h>
#include <inttypes.h>


extern "C" void TIMER1_OVF_vect(void)  __attribute__ ((signal));

struct MAppStruct{
	void (*poll)();
	void (*hw)();
	uint32_t time;
	uint32_t tick;
};


#define PSLOTS 8 //App slots number

class MTask{
	
public:

	static MTask& Instance()
	{
		static MTask    instance;
		return instance;
	}


friend void TIMER1_OVF_vect();


/**
 *  \brief Task Manager Setup
 *  
 *  \return none
 *  
 *  \details Details
 */



~MTask();

void Init(uint32_t, uint32_t);

/**
 *  \brief Start soft work Task Manager
 *  NOTICE: Never returns back!
 *  
 *  \return none
 *  
 *  \details Details
 */
void Start(void);

/**
 *  \brief Start TManager
 *  
 *  \return none
 *  
 *  \details Details
 */
void HwStart(void);

/**
 *  \brief Stop TManager
 *  
 *  \return none
 *  
 *  \details Details
 */
void HwStop(void);

/**
 *  \brief Add function to slot
 *  
 *  \param [in] _poll function pointer
  *  \param [in] _hw function pointer
 *  \param [in] periodic call period in ms
 *  \return 0 if Ok, -1 if error
 *  
 *  \details Details
 */
int8_t Add(void (*_poll)(), void (*_hw)(), uint32_t periodic);


/**
 *  \brief Release active slot
 *  
 *  \param [in] slot slot to release
 *  \return none
 *  
 *  \details Details
 */
void Release(uint8_t slot);

/**
 *  \brief Periodic function
 *  
 *  \return none
 *  
 *  \details Details
 */
void Search();

/**
 *  \brief time after start in ms
 *  
 *  \return time in ms
 *  
 *  \details Details
 */
uint32_t Millis();


uint8_t ActiveApp;

private:
	MTask();
	
	uint8_t getFreeSlot()
	{
		uint8_t slot = PSLOTS;
		for (uint8_t i = 0; i < PSLOTS; ++i)
		{
			if (App[i].hw == 0 && App[i].poll== 0 )
			{
				slot = i;
				break;
			}
		}
		return slot;
	}


	MAppStruct App[PSLOTS];
	
	uint32_t m_timemillis;
	
	uint32_t m_frequency;
	
	uint32_t m_millisPerTick;
};

//extern MTask Task;



#endif /* TASKMANAGER_H_ */
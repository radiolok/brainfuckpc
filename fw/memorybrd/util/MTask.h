/*
 * taskmanager.h
 *
 * Created: 02.01.2013 18:30:36
 *  Author: Artem
 */ 


#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include <avr/interrupt.h>
#include <inttypes.h>

#include "Apps/MApp.h"

extern "C" void TIMER5_OVF_vect(void)  __attribute__ ((signal));

struct MAppStruct{
	MApp* app;
	uint16_t period;
};

#define PSLOTS 8

class MTask{
	
public:

friend void TIMER5_OVF_vect();

MTask(void);//установка таймера.

~MTask();

void Start(void);//разрешает работу диспетчера
void HwStart(void);
void HwStop(void);//Останавливает работу диспетчера
void Add(MApp* _app, uint8_t slot);//записывает фукцию в слот
void Search();

uint32_t millis();

private:

MAppStruct  AppPtr[PSLOTS];

uint8_t Forse;
uint8_t WorkType;//Переменная состояния.
void (*progslot[PSLOTS])();//слоты для программ
uint16_t TPpresc[PSLOTS][2];//а сюда пишем время срабатывания кратное 10мс.

uint32_t Millis;
};

typedef
 struct Foo
 Foo;

extern MTask Task;
#endif /* TASKMANAGER_H_ */
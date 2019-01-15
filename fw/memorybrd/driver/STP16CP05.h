/* 
* STP16CP05.h
*
* Created: 15.01.2019 20:26:20
* Author: radiolok
*/


#ifndef __STP16CP05_H__
#define __STP16CP05_H__


#include "../macros.h"
#include "spi.h"

void STP16CP05_Init();
void STP16CP05_SetColumn(uint8_t column);
void STP16CP05_Blank(uint8_t mode);
void STP16CP05_Latch();


#endif //__STP16CP05_H__

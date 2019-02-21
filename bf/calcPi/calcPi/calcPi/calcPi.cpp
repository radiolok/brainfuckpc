#include <stdio.h>
#include <stdlib.h>

#include "stdafx.h"

#include <stdint.h>
#include <string.h>




void addMov(uint16_t *dst, uint16_t *src)
{
	while (*src)
	{
		(*dst)++;
		(*src)--;
	}
}

void addCpy(uint16_t *dst, uint16_t *src, uint16_t *srcNew)
{
	while (*src)
	{
		(*dst)++;
		(*srcNew)++;
		(*src)--;
	}
}

void subMov(uint16_t *dst, uint16_t *src)
{
	while (*src)
	{
		if (!(*dst))
			break;
		(*dst)--;
		(*src)--;
	}
}

void subCpy(uint16_t *src, uint16_t *sub, uint16_t *subNew)
{
	
	do
	{
		if (!(*src))
		{
			break;
		}
		(*src)--;
		(*subNew)++;
		(*sub)--;
	} while (*sub);
}

void nullCell(uint16_t *cell)
{
	while (*cell)
	{
		(*cell)--;
	}
}

/*dst = dst + src * mul*/
void mul(uint16_t *mem, uint16_t *dst, uint16_t *src, uint16_t *mul)
{
	uint16_t *tmp = mem + 10;	
	nullCell(tmp);

	addCpy(dst, src, tmp);
	(*mul)--;
	while (*mul)
	{
		nullCell(tmp+1);
		//fprintf(stderr, "muL; dst:%d mul:%d; delim: %d\n", *dst, *mul, *tmp);
		addCpy(dst, tmp, tmp + 1);
		tmp++;
		(*mul)--;
	}
}

void divide(uint16_t *mem, uint16_t *result, uint16_t *src, uint16_t *del)
{
	uint16_t *tmp = mem + 10;
	nullCell(tmp);
	subCpy(src, del, tmp);
	if (*del)
		return;
	nullCell(result);
	(*result)++;
	while (*src)
	{
		nullCell(tmp + 1);
		
		subCpy(src, tmp, tmp + 1);

		if (*tmp)
		{
			addMov(src, tmp + 1);
			return;
		}

		(*result)++;
		tmp++;
	}
}


void calcPi(uint16_t *mem)
{
	uint16_t *num = mem;
	uint16_t *denum = mem + 1;
	uint16_t *digit = mem + 2;
	uint16_t *result = mem + 3;
	uint16_t *pos = mem + 4;
	uint16_t *tmp = mem + 5;
	//*digit = 8;

	divide(mem, result, num, denum);
	fprintf(stderr, "Pi=%d.", *result);
	addMov(tmp, num);
	while (*digit)
	{
		uint16_t i = 10;
		uint16_t den = 113;
		nullCell(tmp + 1);
		mul(tmp, tmp + 1 , tmp, &i);
		uint16_t del_mul = *(tmp + 1);
		//fprintf(stderr, "div: src:%d den:%d\n", *(tmp + 1), den);
		divide(tmp, tmp + 2, tmp + 1, &den);
		fprintf(stderr, "%d", *(tmp + 2));
		//fprintf(stderr, " divide(%d/%d) %s, wait %d(%d), got %d(%d)\n", del_mul, 113, ((del_mul) /113 == *(tmp + 2))? "correct": "incorrect",
		//			del_mul /113, del_mul % 113, *(tmp + 2), *(tmp + 1));
		tmp++;
		(*digit)--;
	}

	fprintf(stderr, "\n");

}


int main(void) {
	fprintf(stderr, "Hello world1\n");

	uint16_t a = 355;
	uint16_t b = 113;

	uint16_t memory[65536] = { 0x00 };
	//uint16_t *AP = memory + 0x700;

	uint16_t result = 0;
	uint16_t a_cpy = a;
	uint16_t b_cpy = b;
	memory[0]= 355;
	memory[1] = 113;
	memory[2] = 6;
	calcPi(memory);
	divide(memory, &result, &a_cpy, &b_cpy);
	if (result != (a / b))
	{
		fprintf(stderr, "divide(%d/%d) incorrect, wait %d(%d), got %d (%d)\n", a, b, a / b, a%b, result, a_cpy);

	}
	else
	{
		fprintf(stderr, "divide(%d/%d) correct, wait %d(%d), got %d(%d)\n", a, b, a / b, a%b, result, a_cpy);
	}
	result = 0;
	a_cpy = a;
	b_cpy = b;
	addMov(&a_cpy, &b_cpy);
	fprintf(stderr, "add(%d+%d) %s, wait %d, got %d\n", a, b, (a_cpy != (a + b))? "incorrect": "correct", a + b, a_cpy);

	result = 0;
	a_cpy = a;
	b_cpy = b;
	uint16_t c = 0;
	subCpy(&a_cpy, &b_cpy, &c);
	if (a_cpy != (a - b))
	{
		fprintf(stderr, "sub(%d-%d) incorrect, wait %d, got %d\n", a, b, a - b, a_cpy);

	}
	else
	{
		fprintf(stderr, "sub(%d-%d) correct, wait %d, got %d\n", a, b, a - b, a_cpy);
	}

	result = 0;
	a_cpy = a;
	b_cpy = b;

	mul(memory, &result, &a_cpy, &b_cpy);
	if (result != (a*b))
	{
		fprintf(stderr, "mul(%d*%d) incorrect, wait %d, got %d\n", a, b, a*b, result);

	}
	else
	{
		fprintf(stderr, "mul(%d*%d) correct, wait %d, got %d\n", a, b, a*b, result);
	}


	return 0;
}

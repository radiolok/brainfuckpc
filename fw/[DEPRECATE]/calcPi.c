#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <string.h>

#include <sys/mman.h>


void addMov(uint16_t *dst, uint16_t *src)
{
	while(*src)
	{
		(*dst)++;
		(*src)--;
	}
}

void addCpy(uint16_t *dst, uint16_t *src, uint16_t *srcNew)
{
	while(*src)
	{
		(*dst)++;
		(*srcNew)++;
		(*src)--;
	}
}

void subMov(uint16_t *dst, uint16_t *src)
{
	while(*src)
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
	}while(*sub);
}

void nullCell(uint16_t *cell)
{
	while(*cell)
	{
		(*cell)--;
	}
}

/*dst = dst + src * mul*/
void mul(uint16_t *mem, uint16_t *dst, uint16_t *src, uint16_t *mul)
{
	uint16_t *tmp = mem + 1;
	uint16_t *pos = mem;
	nullcell(pos);
	
	addCpy(dst, src, pos);
	(*mul)--;
	while(*mul)
	{
		addCpy(dst, pos, pos + 1);
		pos++;
		(*mul)--;
	}
}

void divide(uint16_t *mem, uint16_t *dst, uint16_t *src, uint16_t *del)
{
	uint16_t tmp[100] = {0};
	uint16_t pos = 0;
	subCpy(src, del, &tmp[pos]);
	if (*del)
		return;
	(*dst)++;
	(*del)--;
	while(*del)
	{
		//fprintf(stderr, "src:%d dst:%d, delim:%d\n", *src, *dst, tmp[pos]);
		subCpy(src, &tmp[pos], &tmp[pos+1]);

		if (tmp[pos])
		{
			addMov(src, &tmp[pos+1]);
			return;
		}

		(*dst)++;
		pos++;
		(*del)--;
	}
}


void calcPi(uint16_t *mem)
{
	uint16_t num = 355;
	uint16_t denum = 113;
	uint16_t result = 0;
	uint16_t digit = 8;
	uint16_t pos = 0;
	uint16_t tmp[10] = {0x00};


	divide(&result, &num, &denum);
	fprintf(stderr, "Pi=%d.", result);
	addMov(&tmp[pos], &num);
	while (digit)
	{
		uint16_t i = 10;
		uint16_t den = 113;
		nullCell(&tmp[pos+1]);
		mul(&tmp[pos+1], &tmp[pos], &i);
		uint16_t num = tmp[pos+1];
		divide(&tmp[pos+2], &tmp[pos + 1], &den);
		fprintf(stderr, "%d", tmp[pos+2]);
		//fprintf(stderr, " divide(%d/%d) %s, wait %d(%d), got %d(%d)\n", num, 113, (num/113 == tmp[pos+2])? "correct": "incorrect",   num/113, num%113, tmp[pos+2], tmp[pos+1]);
		pos++;
		digit--;
	}
	fprintf(stderr, "\n");

}


int main(void) {
	s_idt_info info;
	fprintf (stderr, "Hello world1\n");

	uint16_t a = 355;
	uint16_t b = 113;

	uint16_t memory[65536]= {0x00};
	uint16_t *AP = memory + 0x700;

	uint16_t result = 0;
	uint16_t a_cpy = a;
	uint16_t b_cpy = b;
	calcPi(memory);
	divide(memory, &result, &a_cpy, &b_cpy);
	if (result != (a/b))
	{
		fprintf(stderr, "divide(%d/%d) incorrect, wait %d(%d), got %d (%d)\n", a, b, a/b, a%b, result, a_cpy);

	}
	else
	{
		fprintf(stderr, "divide(%d/%d) correct, wait %d(%d), got %d(%d)\n", a, b, a/b, a%b, result, a_cpy);
	}
	result = 0;
	a_cpy = a;
	b_cpy = b;
	uint16_t c = 0;
	subCpy(memory, &a_cpy, &b_cpy, &c);
	if (a_cpy != (a-b))
	{
		fprintf(stderr, "sub(%d-%d) incorrect, wait %d, got %d\n", a, b, a-b, a_cpy);

	}
	else
	{
		fprintf(stderr, "sub(%d-%d) correct, wait %d, got %d\n", a, b, a-b, a_cpy);
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


	return EXIT_SUCCESS;
}

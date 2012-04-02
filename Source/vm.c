#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vmDebug.h"
#include "vm.h"

#define EPSILON 0.000001

//Math operations, operates off local variables only, TODO: Change it maybe

static void add(void);
static void sub(void);
static void mul(void);
static void dvd(void);
static void mod(void);
static void sqt(void);
static void pwr(void);

//Logical operations
static void cmp(void);
static void lt(void);
static void lte(void);
static void jmp(void);

//memory
static void mov(void);

static void decode(void);

static int checkType(int opType, int arg1, int arg2, int arg3);

OPCODE opTable[] = {
	&add,
	&sub,
	&mul,
	&dvd,
	&mod,
	&sqt,
	&pwr,
	&cmp,
	&lt,
	&lte,
	&jmp,
	&mov
};

static int * program;

//registers 
static Object * reg;


// program counter
static int * pc;

static int opType;
static int indexA;
static int indexB;
static int indexC;
static int indexD;


int vm_init(int stackSz,int regSz)
{

	reg = (Object*)malloc(sizeof(Object) * regSz);

	if(reg == NULL)
		return -1;

	return 0;

}
int vm_run(int * a_program)
{
	if(reg == NULL)
		return 1;
	if(a_program == NULL)
		return 2;

	program = a_program;
	pc = program;


	for(;;){
		decode();


		if(opType == (DIE))
		{
			printf("dying...\n");
			system("pause");
			break;
		}
	
		opTable[opType]();
		
	}
	return 0;
}

int vm_shutDown()
{
	free(reg);
}


static void add(void)
{
	//add takes two values from designated registers and places result in another register
	
	reg[indexC].value.n = reg[indexA].value.n + reg[indexB].value.n;
	return;
}

static void sub(void)
{
	//sub takes two values from designated registers and places result in another register

	reg[indexC].value.n = reg[indexA].value.n - reg[indexB].value.n;
	return;
}

static void mul(void)
{
	//mul takes two values from designated registers and places result in another register

	reg[indexC].value.n = reg[indexA].value.n * reg[indexB].value.n;
	return;
}

static void dvd(void)
{
	//dvd takes two values from designated registers and places result in another register

	reg[indexC].value.n = reg[indexA].value.n / reg[indexB].value.n;
	return;
}

static void mod(void)
{
	//mod takes two values from designated registers, casts them to int since they could be doubles, mods them 
	//and then places the result in another register

	reg[indexC].value.n = (int)reg[indexA].value.n % (int)reg[indexB].value.n;
	return;
}

static void sqt(void)
{
	//sqt takes a value from the top of the stack takes the sqrt and places result back on top
	
	reg[indexC].value.n = sqrt(reg[indexA].value.n);
	return;
}

static void pwr(void)
{
	//pwr raises indexA to indexB and places the result on top of stack
	
	reg[indexC].value.n = pow(reg[indexA].value.n, reg[indexB].value.n);
	return;
}

static void cmp(void)//todo possibly make a register for this just to seperate the crap
{
	//TODO: possibly change this to just int's
	if(&reg[indexA] == &reg[indexB])
		return;

	if(reg[indexA].type == reg[indexB].type)
	{
		switch(reg[indexA].type)
		{
		case T_NUM:
			pc += (abs(reg[indexA].value.n - reg[indexB].value.n) < EPSILON) ? 0 : 1;
			break;
		case T_BLN:
			pc += (reg[indexA].value.b == reg[indexB].value.b) ? 0 : 1;
			break;
		case T_STR:
			if(reg[indexA].value.s->length <= 0)
				break;
			pc += strncmp(reg[indexA].value.s->string, reg[indexB].value.s->string, reg[indexA].value.s->length) ? 0 : 1;
			break;
		}
	}
	return;
}


static void lt(void)
{
	pc += (reg[indexA].value.n < reg[indexB].value.n) && (fabs(reg[indexA].value.n - reg[indexB].value.n) > EPSILON) ? 0 : 1;
}

static void lte(void)
{
	if(&reg[indexA] == &reg[indexB])
		return;
	pc += (reg[indexA].value.n < reg[indexB].value.n) || (fabs(reg[indexA].value.n - reg[indexB].value.n) < EPSILON) ? 0 : 1;
}

static void jmp(void)
{
	pc = program + indexD;
}

static void mov(void)
{
	reg[indexA] = reg[indexB];	
}

static void decode(void)
{
	//decode opcode into respective parts such as indexes for data etc.

	pc++;

	opType = *pc & 0x000000FF;

	indexA = (*pc >> 8 ) & 0xFF;
	indexB = (*pc >> 16) & 0xFF;
	indexC = (*pc >> 24) & 0xFF;
	indexD = (*pc >> 8);
	
	//TODO: possibly convert to inline
	if( opArgs[opType].check == 3 )
		checkType(opType, reg[indexC].type, reg[indexA].type, reg[indexB].type);
	else if (opArgs[opType].check == 2)
		checkType(opType, reg[indexA].type, reg[indexB].type, T_NONE);
	else if (opArgs[opType].check == 1)
		checkType(opType, reg[indexA].type, T_NONE, T_NONE);
	                                               
}

static int checkType(int opType, Type arg1, Type arg2, Type arg3)
{
	if(opArgs[opType].arg1 != arg1 || opArgs[opType].arg2 != arg2 || opArgs[opType].arg3 != arg3)
	{
		printf("Type Error:\n    %s expected arguments of type %s, %s and %s,\n    got %s and %s instead", opArgs[opType].opName, 
			typeStrings[opArgs[opType].arg1], typeStrings[opArgs[opType].arg2], typeStrings[opArgs[opType].arg3],
			typeStrings[arg1], typeStrings[arg2], typeStrings[arg3]);
		return -1;
	}

	return 0;
}
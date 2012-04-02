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

//variables declared in .data
static Object * heap;


// program counter
static int * pc;

static int opType;
static int indexA;
static int indexB;
static int indexC;
static int indexD;


int vm_init(int stackSz,int heapSz)
{

	heap = (Object*)malloc(sizeof(Object) * heapSz);

	if(heap == NULL)
		return -1;

	return 0;

}
int vm_run(int * a_program)
{
	if(heap == NULL)
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
	free(heap);
}


static void add(void)
{
	//add takes two numbers from top of stack adds them and places result on top of the stack
	
	heap[indexC].value.n = heap[indexA].value.n + heap[indexB].value.n;
	return;
}

static void sub(void)
{
	//sub takes two values from accumulator subs them and places the result on the top of the stack

	heap[indexC].value.n = heap[indexA].value.n - heap[indexB].value.n;
	return;
}

static void mul(void)
{
	//mul takes two values from accumulator multpclies them and places the result on the top of the stack

	heap[indexC].value.n = heap[indexA].value.n * heap[indexB].value.n;
	return;
}

static void dvd(void)
{
	//dvd takes two values from accumulator divides them and places the result on the top of the stack

	heap[indexC].value.n = heap[indexA].value.n / heap[indexB].value.n;
	return;
}

static void mod(void)
{
	//mod takes two values from accumulator, casts them to int since they could be doubles, mods them 
	//and then places the result on the top of the stack

	heap[indexC].value.n = (int)heap[indexA].value.n % (int)heap[indexB].value.n;
	return;
}

static void sqt(void)
{
	//sqt takes a value from the top of the stack takes the sqrt and places result back on top
	
	heap[indexC].value.n = sqrt(heap[indexA].value.n);
	return;
}

static void pwr(void)
{
	//pwr raises indexA to indexB and places the result on top of stack
	
	heap[indexC].value.n = pow(heap[indexA].value.n, heap[indexB].value.n);
	return;
}

static void cmp(void)//todo possibly make a register for this just to seperate the crap
{
	//TODO: possibly change this to just int's
	if(&heap[indexA] == &heap[indexB])
		return;

	if(heap[indexA].type == heap[indexB].type)
	{
		switch(heap[indexA].type)
		{
		case T_NUM:
			pc += (abs(heap[indexA].value.n - heap[indexB].value.n) < EPSILON) ? 0 : 1;
			break;
		case T_BLN:
			pc += (heap[indexA].value.b == heap[indexB].value.b) ? 0 : 1;
			break;
		case T_STR:
			if(heap[indexA].value.s->length <= 0)
				break;
			pc += strncmp(heap[indexA].value.s->string, heap[indexB].value.s->string, heap[indexA].value.s->length) ? 0 : 1;
			break;
		}
	}
	return;
}


static void lt(void)
{
	pc += (heap[indexA].value.n < heap[indexB].value.n) && (fabs(heap[indexA].value.n - heap[indexB].value.n) > EPSILON) ? 0 : 1;
}

static void lte(void)
{
	if(&heap[indexA] == &heap[indexB])
		return;
	pc += (heap[indexA].value.n < heap[indexB].value.n) || (fabs(heap[indexA].value.n - heap[indexB].value.n) < EPSILON) ? 0 : 1;
}

static void jmp(void)
{
	pc = program + indexD;
}

static void mov(void)
{
	heap[indexA] = heap[indexB];	
}

static void decode(void)
{
	//decode opcode into respective parts such as indexes for data etc.

	int instruction = *pc++;

	opType = instruction & 0x000000FF;

	indexA = (instruction >> 8 ) & 0xFF;
	indexB = (instruction >> 16) & 0xFF;
	indexC = (instruction >> 24) & 0xFF;
	indexD = (instruction >> 8);
	
	//TODO: possibly convert to inline
	if( opArgs[opType].check == 3 )
		checkType(opType, heap[indexC].type, heap[indexA].type, heap[indexB].type);
	else if (opArgs[opType].check == 2)
		checkType(opType, heap[indexA].type, heap[indexB].type, T_NONE);
	else if (opArgs[opType].check == 1)
		checkType(opType, heap[indexA].type, T_NONE, T_NONE);
	                                               
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
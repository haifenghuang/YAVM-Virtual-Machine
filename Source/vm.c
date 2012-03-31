#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vmDebug.h"
#include "vm.h"

//Math operations, operates off local variables only, TODO: Change it maybe
static void push(void);
static void pop(void);
static void add(void);
static void sub(void);
static void mul(void);
static void dvd(void);
static void mod(void);
static void sqt(void);
static void pwr(void);

//Logical operations
static void cmp(void);
static void jne(void);
static void jie(void);
static void jmp(void);
static void mov(void);


static void flsh(void);
static void decode(void);



static int checkType(int opType, int arg1, int arg2);

typedef enum
{
	//math
	PUSH,
	POP,
	ADD,
	SUB,
	MUL,
	DVD,
	MOD,
	SQT,
	PWR,
	//logic not really
	CMP,
	JNE,
	JIE,
	JMP,
	//control codes
	FLSH,
	MOV,
	DIE = 255
}OPCODES;



OPCODE opTable[] = {
	&push,
	&pop,
	&add,
	&sub,
	&mul,
	&dvd,
	&mod,
	&sqt,
	&pwr,
	&cmp,
	&jne,
	&jie,
	&jmp,
	&flsh,
	&mov
};

static int * program;
//stack of "number" that is used for data manpculation 
static Object * stack;
//variables declared in .data
static Object * heap;


// program counter
static int * pc;
// Stack Pointer
static Object * sp;

static int opType;
static int indexA;
static int indexB;
static int indexC;


int vm_init(int stackSz,int heapSz)
{
	stack = (Object*)malloc(sizeof(Object) * stackSz);
	sp = stack;

	if(stack == NULL)
		return -1;

	heap = (Object*)malloc(sizeof(Object) * heapSz);

	if(heap == NULL)
		return -1;

	return 0;

}
int vm_run(int * a_program)
{
	if(heap == NULL || stack == NULL)
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

		if(abs(sp-stack)> 31)
		{
			printf("Error:\n    stack overflow,\n    last operation %s\n",opArgs[opType].opName);
			system("pause");
			exit(-1);
		}
		
	}
	return 0;
}

int vm_shutDown()
{
	free(stack);
	free(heap);

}


static void push(void)
{
	//pushes indexA to stack
	*++sp = heap[indexA];
	return;
}

static void pop(void)
{
	//pops the last value off the stack into indexA
	heap[indexA] = *sp--;
	return;
}

static void add(void)
{
	//add takes two numbers from top of stack adds them and places result on top of the stack
	
	(++sp)->value.n = heap[indexA].value.n + heap[indexB].value.n;
	sp->type = T_NUM;
	
	return;
}

static void sub(void)
{
	//sub takes two values from accumulator subs them and places the result on the top of the stack

	(++sp)->value.n = heap[indexA].value.n - heap[indexB].value.n;
	sp->type = T_NUM;
	return;
}

static void mul(void)
{
	//mul takes two values from accumulator multpclies them and places the result on the top of the stack

	(++sp)->value.n = heap[indexA].value.n * heap[indexB].value.n;
	sp->type = T_NUM;
	return;
}

static void dvd(void)
{
	//dvd takes two values from accumulator divides them and places the result on the top of the stack

	(++sp)->value.n = heap[indexA].value.n / heap[indexB].value.n;
	sp->type = T_NUM;	
	return;
}

static void mod(void)
{
	//mod takes two values from accumulator, casts them to int since they could be doubles, mods them 
	//and then places the result on the top of the stack

	(++sp)->value.n = (int)heap[indexA].value.n % (int)heap[indexB].value.n;
	sp->type = T_NUM;
	return;
}

static void sqt(void)
{
	//sqt takes a value from the top of the stack takes the sqrt and places result back on top
	
	(++sp)->value.n = sqrt(heap[indexA].value.n);
	sp->type = T_NUM;
	return;
}

static void pwr(void)
{
	//pwr raises indexA to indexB and places the result on top of stack
	
	(++sp)->value.n = pow(heap[indexA].value.n, heap[indexB].value.n);
	sp->type = T_NUM;
	return;
}

static void cmp(void)//todo possibly make a register for this just to seperate the crap
{
	//TODO: possibly change this to just int's
	if(&heap[indexA] == &heap[indexB]){
		(++sp)->value.b = TRUE;
		sp->type = T_BLN;
		return;
	}

	if(heap[indexA].type == heap[indexB].type)
	{
	    ++sp;
		sp->type = T_BLN;

		switch(heap[indexA].type)
		{
		case T_NUM:
			sp->value.b = (abs(heap[indexA].value.n - heap[indexB].value.n) < 0.00001) ? TRUE : FALSE;
			break;
		case T_BLN:
			sp->value.b = (heap[indexA].value.b == heap[indexB].value.b) ? TRUE : FALSE;
			break;
		case T_STR:
			if(heap[indexA].value.s->length <= 0)
			{
				sp->value.b = FALSE;
				break;
			}
			sp->value.b = strncmp(heap[indexA].value.s->string, heap[indexB].value.s->string, heap[indexA].value.s->length) ? FALSE : TRUE;
			break;
		}
	}
			
	sp->type = T_BLN;
	return;
}

static void jne(void)//consumes item on top of stack
{
	
	if((sp--)->value.b == FALSE)
		pc = program + indexC;
	return;
}

static void jie(void)//consumes item on top of stack to check if true and uses indexC as jump address
{
	
	if((sp--)->value.b == TRUE)
		pc = program + indexC;
	return;
}

static void jmp(void)
{
	pc = program + indexC;
}

static void flsh(void)
{
	sp = stack;
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

	indexA = (instruction >> 8 ) & 0x000000FF;
	indexB = (instruction >> 16) & 0x000000FF;
	indexC = (instruction >> 8);
	
	if( opArgs[opType].check == 2 )
		checkType(opType, heap[indexA].type, heap[indexB].type);
	else if (opArgs[opType].check == 1)
		checkType(opType, T_NONE, heap[indexA].type);
	                                               
}

static int checkType(int opType, int arg1, int arg2)
{
	if(opArgs[opType].arg1 != arg1 || opArgs[opType].arg2 != arg2)
	{
		printf("Type Error:\n    %s expected arguments of type %s and %s,\n    got %s and %s instead",
			opArgs[opType].opName, typeStrings[opArgs[opType].arg1], typeStrings[opArgs[opType].arg2], typeStrings[arg1], typeStrings[arg2]);
		return -1;
	}

	return 0;
}
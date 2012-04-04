#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "vmDebug.h"
#include "vm.h"
#include "types.h"


static int checkType(int opType, int arg1, int arg2, int arg3);

static int * program;

//registers 
static Object reg[1024];

// program counter
static int * pc;

static OPCODE opType;
static int indexA;
static int indexB;
static int indexC;
static int indexD;

static void * opTable[12]; // stores label addresses 

int vm_run(int * a_program)
{
	if(a_program == NULL)
		return 2;

	program = a_program;
	pc = program;

	__asm //grab label addresses and populate optable
	{
		mov eax, op_add;
		mov [opTable + OP_ADD*4], eax;
		mov eax, op_sub;
		mov [opTable + OP_SUB*4], eax;
		mov eax, op_mul;
		mov [opTable + OP_MUL*4], eax;
		mov eax, op_div;
		mov [opTable + OP_DIV*4], eax;
		mov eax, op_mod;
		mov [opTable + OP_MOD*4], eax;
		mov eax, op_sqrt;
		mov [opTable + OP_SQRT*4], eax;
		mov eax, op_pow;
		mov [opTable + OP_POW*4], eax;
		mov eax, op_cmp;
		mov [opTable + OP_CMP*4], eax;
		mov eax, op_lt;
		mov [opTable + OP_LT*4], eax;
		mov eax, op_lte;
		mov [opTable + OP_LTE*4], eax;
		mov eax, op_jmp;
		mov [opTable + OP_JMP*4], eax;
		mov eax, op_mov;
		mov [opTable + OP_MOV*4], eax;
	}

next_opcode:

	//Decode instruction
	opType = (OPCODE)(*pc & 0x000000FF); // cast just to get visual c++ to shutup

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

	++pc;

	if(opType == (DIE))
	{
		fprintf(stderr,"dying, ran %d instructions\n", abs(program-pc));
		return 0;
	}
	_asm
	{
		mov eax, opType;
		mov eax, [opTable + eax*4];
		jmp eax;
	}

op_add:
	reg[indexA].value.n = reg[indexB].value.n + reg[indexC].value.n;
	goto next_opcode;
op_sub:
	reg[indexA].value.n = reg[indexB].value.n - reg[indexC].value.n;
	goto next_opcode;
op_mul:
	reg[indexA].value.n = reg[indexB].value.n * reg[indexC].value.n; 
	goto next_opcode;
op_div:
	reg[indexA].value.n = reg[indexB].value.n / reg[indexC].value.n; 
	goto next_opcode;
op_mod:
	reg[indexA].value.n = (int)reg[indexB].value.n % (int)reg[indexC].value.n; 
	goto next_opcode;
op_sqrt:
	reg[indexA].value.n = sqrt((double)reg[indexB].value.n);
	goto next_opcode;
op_pow:
	reg[indexA].value.n = pow((double)reg[indexB].value.n, reg[indexC].value.n);
	goto next_opcode;
//cmp, lt, and lte are naive implementations of comparision and don't take float/double into accont
op_cmp:
	if(&reg[indexA] == &reg[indexB])
		goto next_opcode;
	if(reg[indexA].type == reg[indexB].type)
	{
		switch(reg[indexA].type)
		{
		case T_NUM:
			if(reg[indexA].value.n == reg[indexB].value.n)
				++pc;
			break;
		case T_BLN:
			if(reg[indexA].value.b == reg[indexB].value.b)
				++pc;
			break;
		case T_STR:
			if(reg[indexA].value.s->length <= 0)
				break;
			pc += strncmp(reg[indexA].value.s->string, reg[indexB].value.s->string, reg[indexA].value.s->length) ? 0 : 1;
			break;
		}
	}
	goto next_opcode;
op_lt:
	if(reg[indexA].value.n >= reg[indexB].value.n)
		++pc;
	goto next_opcode;
op_lte:
	if(reg[indexA].value.n > reg[indexB].value.n)
		++pc;
	goto next_opcode;
op_jmp:
	pc = program + indexD;
	goto next_opcode;
op_mov:
	reg[indexA] = reg[indexB];	
	goto next_opcode;
}

static int checkType(int opType, Type arg1, Type arg2, Type arg3) //TODO: possibly make inline
{
	if(opArgs[opType].arg1 != arg1 || opArgs[opType].arg2 != arg2 || opArgs[opType].arg3 != arg3)
	{
		fprintf(stderr, "Type Error:\n    %s expected arguments of type %s, %s, %s\n    got %s, %s, %s instead\n", opArgs[opType].opName, 
			typeStrings[opArgs[opType].arg1], typeStrings[opArgs[opType].arg2], typeStrings[opArgs[opType].arg3],
			typeStrings[arg1], typeStrings[arg2], typeStrings[arg3]);
		return -1;
	}

	return 0;
}
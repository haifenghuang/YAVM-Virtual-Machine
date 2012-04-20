#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "vm.h"
#include "object.h"
#include "vm_asm.h"

static Object memory[1024]; // memory is not yet dynamic, kinda defeats the purpose
static int * pc;

static OPCODE opType;
static int iA; // index into a register
static int iB; // index into a local variable
static int iC; // index into a local variable
static int iD; // index into global, constant or offset for jmp
static int siD;

static void * opTable[OP_NUM]; // stores label addresses 

int vm_run(int * program)
{
	if(program == NULL)
		return 2;

	pc = program;

	// look in "vm_asm.h"
	ASM_POPULATE_OPTABLE // macro for assembly code

next_opcode:

	//Decode instruction
	++pc;

	ASM_VM_GOTO(opType);

op_add:
	memory[iA].value.n += memory[iB].value.n;
	goto next_opcode;
op_sub:
	memory[iA].value.n -= memory[iB].value.n;
	goto next_opcode;
op_mul:
	memory[iA].value.n *= memory[iB].value.n;
	goto next_opcode;
op_div:
	memory[iA].value.n /= memory[iB].value.n;
	goto next_opcode;
op_mod:
	memory[iA].value.n %= memory[iB].value.n;
	goto next_opcode;
op_sqrt:
	memory[iA].value.n = sqrt((double)memory[iA].value.n);
	goto next_opcode;
op_pow:
	memory[iA].value.n = pow((float)memory[iA].value.n, memory[iB].value.n);
	goto next_opcode;
//cmp, lt, and lte are naive implementations of comparision and don't take float/double into accont
op_cmp:
	if((&memory[iA] == &memory[iB]) || (memory[iA].value.n == memory[iB].value.n))
		goto next_opcode;
	else if (memory[iA].type == T_STR && memory[iB].type == T_STR)
	{
		pc += strncmp(memory[iA].value.s->string, memory[iB].value.s->string, memory[iA].value.s->length);
	}
	else pc++;

	goto next_opcode;

op_lt:
	if(memory[iA].value.n >= memory[iA].value.n)
		++pc;
	goto next_opcode;
op_lte:
	if(memory[iA].value.n > memory[iA].value.n)
		++pc;
	goto next_opcode;
op_jmp:
	pc += siD;
	goto next_opcode;
op_mov:
	memory[iA] = memory[iB];
	goto next_opcode;
op_end:
	return 0;

	
}


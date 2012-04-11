#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "vm_debug.h"
#include "vm.h"
#include "object.h"
#include "vm_asm.h"

#define localA (base+iA) // pointer to base[iA]
#define localB (base+iB)
#define localC (base+iC)

#define constD (constants + iD)

//baseisters 
static Object constants[1024] = {
	{T_NUM, {1234}},
	{T_NUM, {8765}}

};
static Object stack[1024]; // stack is not yet dynamic kinda defeats the purpose
static Object * tos = stack;
static Object * base = stack;
static Function * functionTable;//when code is compiled this will be a list of all functions
static Function * currentFunction;
// program counter
static int * pc;

static OPCODE opType;
static int iA; // index into a register
static int iB; // index into a local variable
static int iC; // index into a local variable
static int iD; // index into global, constant or offset for jmp

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
	
	opType = GETOP(*pc);
	iA = GETARG_A(*pc);
	iB = GETARG_B(*pc);
	iC = GETARG_C(*pc);
	iD = GETARG_D(*pc);

	++pc;

	ASM_VM_GOTO(opType);

op_push:
	++tos;
	*tos = *localA;
	goto next_opcode;
op_pushk:
	++tos;
	*tos = *constD;
	goto next_opcode;
op_add:
	valuen(localA) = valuen(localB) + valuen(localC);
	goto next_opcode;
op_sub:
	valuen(localA) = valuen(localB) - valuen(localC);
	goto next_opcode;
op_mul:
	valuen(localA) = valuen(localB) * valuen(localC);
	goto next_opcode;
op_div:
	valuen(localA) = valuen(localB) / valuen(localC); 
	goto next_opcode;
op_mod:
	valuen(localA) = (int)valuen(localB) % (int)valuen(localC); 
	goto next_opcode;
op_sqrt:
	valuen(localA) = sqrt((double)valuen(localB));
	goto next_opcode;
op_pow:
	valuen(localA) = pow((double)valuen(localB), valuen(localC));
	goto next_opcode;
//cmp, lt, and lte are naive implementations of comparision and don't take float/double into accont
op_cmp:
	if(localA == localB)
		goto next_opcode;
	if(type(localA) == type(localB))
	{
		switch(type(localA))
		{
		case T_NUM:
			if(valuen(localA) == valuen(localB))
				++pc;
			break;
		case T_BLN:
			if(valuen(localA) == valuen(localB))
				++pc;
			break;
		case T_STR:
			if(values(localA)->length <= 0)
				break;
			pc += strncmp(values(localA)->string, values(localB)->string, values(localA)->length) ? 0 : 1;
			break;
		}
	}
	goto next_opcode;
op_lt:
	if(valuen(localA) >= valuen(localB))
		++pc;
	goto next_opcode;
op_lte:
	if(valuen(localA) > valuen(localB))
		++pc;
	goto next_opcode;
op_jmp:// can only jump forward
	pc += iD;
	goto next_opcode;
op_mov:
	*localA = *localB;	
	goto next_opcode;
op_call:
	//push return address
	++tos;
	tos->value.ret = (pc + 1);
	//push base pointer
	++tos;
	tos->value.bp = base;
	++tos;
		
	currentFunction = functionTable + iD;
	pc = functionTable[iD].code;
		
	base = tos;
	tos += functionTable[iD].localsSz;
	goto next_opcode;

op_ret:
	--tos;
	pc = tos->value.ret;
	--tos;
	base = tos->value.bp;
	goto next_opcode;

op_end:
	return 0;

	
}


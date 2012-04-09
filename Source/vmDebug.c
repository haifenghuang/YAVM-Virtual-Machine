#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

#include "vmDebug.h"
#include "vm.h"

const opInfo opArgs[]  = {
	      //indexA  indexB  indexC
	{"ADD", T_NUM,  T_NUM,  T_NUM,  3 },
	{"SUB", T_NUM,  T_NUM,  T_NUM,  3 },
	{"MUL", T_NUM,  T_NUM,  T_NUM,  3 },
	{"DIV", T_NUM,  T_NUM,  T_NUM,  3 },
	{"MOD", T_NUM,  T_NUM,  T_NUM,  3 },
	{"SQRT", T_NUM,  T_NUM,  T_NONE, 3 },
	{"POW", T_NUM,  T_NUM,  T_NUM,  3 },
	{"CMP", T_OBJ, T_OBJ, T_NONE, 2 },   //every type is object so there is no need to check so this is for printing, TODO: change this
	{"LT",  T_NUM,  T_NUM,  T_NONE, 2 }, //jne takes no arguments
	{"LTE", T_NUM, T_NUM,   T_NONE, 2 }, //jie takes no arguments
	{"JMP", T_NONE, T_NONE, T_NONE, 4 }, //jmp takes argument D but does not need checking
	{"MOV", T_OBJ, T_OBJ, T_OBJ, 3 },
	{"CALL", T_FRAME, T_NONE, T_NONE, 1}
};


const char * getDebugInfo(int errorCode)
{
	switch(errorCode)
	{
	case 1:
		return "Error:\n    argument a_program was NULL";
	case 2:
		return "Error:\n    stack and heap not initialized, call:\n    vm_init(int stackSz, int heapSz) before vm_run";
	default:
		return NULL;
	}
}


int printProgram(int * program)
{
	int opType;
	int indexA;
	int indexB;
	int indexC;
	int indexD;
	const char * opName;

	if(program == NULL) 
		return -1;

next_opcode:

	opType = (OPCODE)(*program & 0x000000FF); // cast just to get visual c++ to shutup

	indexA = (*program >> 8 ) & 0xFF;
	indexB = (*program >> 16) & 0xFF;
	indexC = (*program >> 24) & 0xFF;
	indexD = (*program >> 8);

	opName = opArgs[opType].opName;

	if(opArgs[opType].check == 3)
		printf("%s %d, %d, %d \n", opName, indexA, indexB, indexC);
	else if(opArgs[opType].check == 2)
		printf("%s %d, %d\n", opName, indexA, indexB);
	else if(opArgs[opType].check == 1)
		printf("%s %d\n", opName, indexA);
	else if(opArgs[opType].check == 4)
		printf("%s %d\n", opName, indexD);
	
	program++;

	if(opType == (DIE))
	{	
		return 0;
	}

	goto next_opcode;

};
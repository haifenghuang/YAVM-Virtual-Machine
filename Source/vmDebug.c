#include <stdlib.h>
#include "types.h"

#include "vmDebug.h"

const opInfo opArgs[]  = {
	      //indexA  indexB  indexC
	{"ADD", T_NUM,  T_NUM,  T_NUM,  3 },
	{"SUB", T_NUM,  T_NUM,  T_NUM,  3 },
	{"MUL", T_NUM,  T_NUM,  T_NUM,  3 },
	{"DIV", T_NUM,  T_NUM,  T_NUM,  3 },
	{"MOD", T_NUM,  T_NUM,  T_NUM,  3 },
	{"SQRT", T_NUM,  T_NUM,  T_NONE, 3 },
	{"POW", T_NUM,  T_NUM,  T_NUM,  3 },
	{"CMP", T_NONE, T_NONE, T_NONE, 0 },
	{"LT",  T_NUM,  T_NUM,  T_NONE, 2 }, //jne takes no arguments
	{"LTE", T_NUM, T_NUM,   T_NONE, 2 }, //jie takes no arguments
	{"JMP", T_NONE, T_NONE, T_NONE, 0 }, //jmp takes no arguments
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


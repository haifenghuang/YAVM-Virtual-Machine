#include <stdlib.h>
#include "vmDebug.h"

#define OPNUM 13

const opInfo opArgs[]  = {
	{"PUSH",T_NONE, T_OBJ, 0 }, // PUSH requires object type
	{"POP", T_NONE, T_OBJ, 0 }, // POP requires object type
	{"ADD", T_NUM,  T_NUM, 2 },
	{"SUB", T_NUM,  T_NUM, 2 },
	{"MUL", T_NUM,  T_NUM, 2 },
	{"DVD", T_NUM,  T_NUM, 2 },
	{"MOD", T_NUM,  T_NUM, 2 },
	{"SQT", T_NONE, T_NUM, 1 },
	{"PWR", T_NUM,  T_NUM, 2 },
	{"CMP", T_OBJ,  T_OBJ, 0 },
	{"JNE", T_NONE, T_NONE, 0 }, //jne takes no arguments
	{"JIE", T_NONE, T_NONE, 0 }, //jie takes no arguments
	{"JMP", T_NONE, T_NONE, 0 }, //jmp takes no arguments
	{"FLSH",T_NONE, T_NONE, 0 }, //flsh takes no arguments
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
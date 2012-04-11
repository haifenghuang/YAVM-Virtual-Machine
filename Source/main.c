#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
#include "vm_debug.h"

int program[]  = {
	SETINS(OP_PUSHK, 0, 0, 0),
	SETINS(OP_PUSHK, 1, 0, 0),
	SETINS(OP_ADD,   0, 0, 1),

	SETINS(OP_END,   0, 0, 0)
};


int main(int argc, char *argv[])
{


	
	printProgram(program);
	vm_run(program);
	return 0;
}
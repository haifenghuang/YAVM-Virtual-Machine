#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
int program[]  = {
	SETINSABC(OP_END,   0, 0, 0)
};





int main(int argc, char *argv[])
{
	vm_run(program);
	return 0;
}
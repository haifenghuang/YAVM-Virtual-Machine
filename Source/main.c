#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
#include "vmDebug.h"


int program[]  = {
	0x00010007,
	0x01000000,
	DIE
};

int main(int argc, char *argv[])
{


	vm_init();
	printf(getDebugInfo(vm_run(program)));
	vm_shutDown();
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
#include "vmDebug.h"


int program[]  = {
	0x00000000,
	DIE
};

int main(int argc, char *argv[])
{
	vm_init(32, 32);
	printf(getDebugInfo(vm_run(NULL)));
	vm_shutDown();
	return 0;
}
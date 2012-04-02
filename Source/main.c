#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
#include "vmDebug.h"


int program[]  = {
	0x00000000,
	0x00020007,
	0x0001000B,
	DIE
};

int main(int argc, char *argv[])
{
	vm_init();
	vm_run(program);
	vm_shutDown();
}
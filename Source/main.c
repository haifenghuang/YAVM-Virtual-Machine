#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
#include "vmDebug.h"


int program[]  = {
	0x00010200, //add
	0x01000200, //add
	0x00010009, //cmp
	0x00000A0A, //
	0x0100020B,
	0x0201000B,
	0x00020007,
	0x0001000B,
	0x00010202,
	0x02010002,
	DIE
};
char test[3] = {'a', 'b', 'c'};


int main(int argc, char *argv[])
{
	printProgram(program);
	return 0;
	//vm_run(program);
}
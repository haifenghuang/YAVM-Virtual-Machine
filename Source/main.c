#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
#include "vmDebug.h"


int program[]  = {
	0x00010200,
	0x01000200,
	0x00010009,
	0x0001020B,
	0x0100020B,
	0x0201000B,
	0x00020007,
	0x0001000B,
	0x00010202,
	0x02010002,
	DIE
};


int main(int argc, char *argv[])
{
	int a = 0, b= 1;
	if(a == b)
		a = 5;
	//vm_run(program);
}
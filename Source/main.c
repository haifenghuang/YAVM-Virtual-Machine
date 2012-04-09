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
char test[3] = {'a', 'b', 'c'};

unsigned int hashFunction(const char * string, int length, int sz)
{
	int i;
	unsigned short n = 0;
	unsigned short * iString = (unsigned short*)string;

	for(i = 0; i < length/sizeof(short); i++)
	{
		n += iString[i] + i;
	}

	return n % sz;
}

int main(int argc, char *argv[])
{
	unsigned int a;
	a = hashFunction("abcdef", 6, 100);
	//vm_run(program);
}
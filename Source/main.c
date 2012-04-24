#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"

int program[] = {
	0x00000010, //LOADG R(0), G(0)
	0x00010110, //LOADG R(1), G(1)
	0x00010000, //ADD R(0), R(1), R(0)
	0x01000013, //GT  R(0), R(1), R(0)
	0x80010015, //JE  R(0), SIMM16
	0x00020210, //LOADG R(2), G(2)
	0x000000ff  //END
};

int main(int argc, char *argv[])
{

	YAVM_run(program);
	return 0;
}
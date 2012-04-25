#include "vm.h"

int program[] = {
	0x0000000f, //PUSH R(0) i.e. sp++
	0x00000019, //CALL methods[0];
	0x000000ff  //END
};

int derpAddMethod[] = {
	0x00010001,
	0x0000001A
};

int main(int argc, char *argv[])
{
	YAVM_Method m;
	m.argSize = 2;
	m.code = derpAddMethod;
	m.localsSize = 0;

	YAVM_setMethod(m, 0);


	YAVM_run(program);
	return 0;
}
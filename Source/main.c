#include "vm.h"

int program[] = {
	0x0000000f, //PUSH R(0) i.e. sp++
	0x00000019, //CALL methods[0], IMM8;
	0x000000ff  //END
};

int delegateF[] = {//methods[0] argsize = 1 locals = 1
	0x0000000f, //PUSH R(0) i.e. sp++
	0x0000000f, //PUSH R(0) i.e. sp++
	0x00000119, //CALL methods[0], IMM8;
	0x0000011A  //RET R(1)
};

int derpAddMethod[] = {
	0x00010001, //ADD R(0), R(1), R(2)
	0x0000001A  //RET R(0)
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
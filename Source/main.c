#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
int fibo[] = {// R(0) = n
	0x0000011C, // MOV R(1), 0          1:  a = 0
	0x0001021C, // MOV R(2), 0          2:  b = 1
	0x0000031C, // MOV R(3), 0          3:  sum = 0
	0x0000041C, // MOV R(4), 0          4:  i = 0

	0x00000324, // PRINT R(3)			9:  print(sum)
	0x00020111, // MOV R(1), R(2)       6:  a = b
	0x00030211, // MOV R(2), R(3)       7:  b = sum
	0x02010301, // ADD R(3), R(1), R(2) 5:  sum = a+b
	0x0001041D, // ADD R(4), 1          8:  i += 1
	0x00000416, // GTE R(4),R(0)		10: if(i < n)
	0x7FFFF918, //						11:   goto 1
	0x0000031A  // RET R(3)             12: return sum
};

int mainM[] = {
	0x0000000F, // PUSH R(0)            
	0x00000019, // CALL 0               : fibo(5)
	0x000000FF  // END
};

int main(int argc, char *argv[])
{
	clock_t start;
	int numofiterations;
	int i;
	YAVM_Method m;
	m.argSize = 1;
	m.code = fibo;
	m.localsSize = 4;
	
	printf("Hello, welcome to the YAVM fibonacci demo. \nHow many iterations shall be performed?\n");
	scanf("%d", &numofiterations);
	printf("\nStarting execution:\n");
	YAVM_init();
	YAVM_setStack(0, numofiterations);
	YAVM_setMethod(m, 0);
	start = clock();
	i = YAVM_run(mainM);
	printf("\nPerformed %d iterations, \nNumber of instructions executed:%d \nExecution time(ms):%f\n\n",numofiterations, i, (((double)clock() - start) / CLOCKS_PER_SEC)*1000);
	system("pause");
	return 0;
}
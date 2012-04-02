#ifndef VM_H
#define VM_H	
#include "types.h"

typedef enum
{
	ADD,
	SUB,
	MUL,
	DVD,
	MOD,
	SQT,
	PWR,
	CMP,
	LT,
	LTE,
	JMP,
	MOV,
	DIE = 255
}OPCODES;


int vm_init(void);
int vm_run(int * program);
int vm_shutDown();



#endif
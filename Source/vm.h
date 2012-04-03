#ifndef VM_H
#define VM_H	

typedef enum
{
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_SQRT,
	OP_POW,
	OP_CMP,
	OP_LT,
	OP_LTE,
	OP_JMP,
	OP_MOV,
	DIE = 255
}OPCODE;


int vm_run(int * program);




#endif
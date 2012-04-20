#ifndef VM_H
#define VM_H	

#define OP_NUM 12

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
	OP_END // shutdown virtual machine
}OPCODE;

struct Instruction
{
	int opcode;
	int operands;
}

#define 

int vm_run(int * program);




#endif
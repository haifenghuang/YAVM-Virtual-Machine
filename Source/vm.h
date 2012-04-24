#ifndef VM_H
#define VM_H	

//Math
#define ADD		0
#define SUB		2
#define MUL		3
#define DIV		4
#define MOD		5
#define SQRT	6
#define EXP		7
//Float Math
#define FADD	8
#define FSUB	9
#define FMUL	10
#define FDIV	11
#define FMOD	12
#define FSQRT	13
#define FEXP	14
//Memory Operations
#define MOV		15
#define LOADG   16
#define SETG	17
//Assignment Comparisons
#define CMP     18
#define GT      19
#define GTE		20
//Jump on variable
#define JE      21
#define JMP		22
#define END     255
/*
typedef struct YAVM_Method YAVM_Method;
typedef struct YAVM_State YAVM_State;

struct YAVM_Method
{
	int argSize;
	int localsSize;
	int * code;
};


struct YAVM_State
{
	int * code;
	YAVM_Method * methods;
};
*/
int YAVM_run(int * code);

#endif
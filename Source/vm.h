#ifndef VM_H
#define VM_H	

//Math
#define ADD		1
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
#define PUSH    15
#define POP     16
#define MOV		17
#define LOADG   18
#define SETG	19
//Assignment Comparisons
#define CMP     20
#define GT      21
#define GTE		22
//Jump on variable
#define JE      23
#define JMP		24
#define CALL    25
#define RET     26
#define LOADRET 27
#define END     255

typedef struct YAVM_Method YAVM_Method;

//typedef struct YAVM_State YAVM_State;



struct YAVM_Method
{
	int argSize;    //how many arguments
	int localsSize; //how many locals, sp++
	int * code;
};


/*
struct YAVM_State
{
	int * code;
	YAVM_Method * methods;
};
*/
int YAVM_run(int * code);
int YAVM_setMethod(YAVM_Method method, int index);

#endif
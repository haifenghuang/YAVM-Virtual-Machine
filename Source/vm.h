#ifndef VM_H
#define VM_H	

#define OP_NUM 16

// encodes A, B and C indexes implicity encodes D 
#define SETINSABC(o, a, b, c) (c << 24) | ((b & 0xFF) << 16) | ((a & 0xFF) << 8) | (o & 0xFF) 
//encodes d
#define SETINSD(o, d)((d<<8) | (o & 0xFF))

#define SETOP(i, o)(i = i & (o & 0xFF))  
#define SETARG_A(i, a)(i = i & (a & 0xFF) << 8)
#define SETARG_B(i, b)(i = i & (b & 0xFF) << 16)
#define SETARG_C(i, c)(i = i & (c & 0xFF) << 24)
#define SETARG_D(i, d)(i = i & (d << 8 ))

#define GETOP(i)(i) & 0xFF
#define GETARG_A(i)(i >> 8 ) & 0xFF
#define GETARG_B(i)(i >> 16) & 0xFF
#define GETARG_C(i)(i >> 24) & 0xFF
#define GETARG_D(i)(i >> 8 )

#define BIAS(n)(n+8388608)

typedef enum
{
	OP_PUSH,
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
	OP_CALL,
	OP_RET,
	OP_END // shutdown virtual machine
}OPCODE;


int vm_run(int * program);




#endif
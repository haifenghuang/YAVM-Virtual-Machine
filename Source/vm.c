#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"

#define MAX_STACK 1024
#define MAX_METHODS 64

static YAVM_Method methods[MAX_METHODS];
static int globals[1024] = {1, 1, 1234, 4, 5, 0};
static int stack[MAX_STACK]= {0, 0}; // used for locals and args

static int * sp = stack;
static int * bp = stack+1;
static float * fbp;

static int cstack[MAX_STACK];// used for bp, sp, and pc
static int * csp = cstack; 

static int * pc;

#define SIGN24 0x00800000 // (2 ^ 24)/2
#define SIGN16 0x00008000 // (2 ^ 16)/2

#define OP ((instruction) & 0xFF)			//opcode
#define RA bp[((instruction >> 8 ) & 0xFF)] //tos[rA] 
#define RB bp[((instruction >> 16) & 0xFF)] //tos[rB]
#define RC bp[((instruction >> 24) & 0xFF)] //tos[rC]

#define FRA fbp[((instruction >> 8 ) & 0xFF)]
#define FRB fbp[((instruction >> 16) & 0xFF)] //tos[rB]
#define FRC fbp[((instruction >> 24) & 0xFF)] //tos[rC]

#define IMM16   (instruction >> 16) & 0xFFFF
#define SIMM16 ((instruction >> 16) & 0xFFFF) - SIGN16
#define IMM24   (instruction >> 8) & 0xFFFFFF
#define SIMM24 ((instruction >> 8) & 0xFFFFFF) - SIGN24

#define G(i)globals[i]

int YAVM_setMethod(YAVM_Method method, int index)
{
	if(index > MAX_METHODS)
		return -1;
	methods[index] = method;
	return 0;
}

int YAVM_run(int * program)
{
	int instruction = SIGN24;
	if(program == NULL)
		return -1;
	pc = program;

next_opcode:
	instruction = *pc;
	fbp = (float*)bp;
	++pc;

	switch(OP){
	case ADD:
		RA = RB + RC;
		break;
	case SUB:
		RA = RB - RC;
		break;
	case MUL:
		RA = RB * RC;
		break;
	case DIV:
		RA = RB / RC;
		break;
	case MOD:
		RA = RB % RC;
		break;
	case SQRT:
		RA = (int)sqrt((float)RB);
		break;
	case EXP:
		RA = (int)pow((float)RB, RC);
		break;
	case FADD:
		FRA = FRB + FRC;
		break;
	case FSUB:
		FRA = FRB - FRC;
		break;
	case FMUL:
		FRA = FRB * FRC;
		break;
	case FDIV:
		FRA = FRB / FRC;
		break;
	case FMOD:
		FRA = fmod(FRB, FRC);
		break;
	case FSQRT:
		FRA = sqrt(FRB);
		break;
	case FEXP:
		FRA = pow(FRB, FRC);
		break;
	case PUSH:
		*(++sp) = RA;
		break;
	case POP:
		RA = *(sp--);
		break;
	case MOV:
		RA = RB;
		break;
	case LOADG:
		RA = G(IMM16);
		break;
	case SETG:
		G(IMM16) = RA;
		break;
	case CMP:
		RA = (RB == RC);
		break;
	case GT:
		RA = (RB > RC);
		break;
	case GTE:
		RA = (RB >= RC);
		break;
	case JE:
		pc += RA ? SIMM16 : 0;
		break;
	case JMP:
		pc += SIMM24;
		break;
	case CALL:

		*(++csp) = (int)pc;
		*(++csp) = (int)bp;
		*(++csp) = (int)sp;

		bp = sp - methods[IMM24].argSize + 1; 
		sp += methods[IMM24].localsSize;//TODO check ofr stack overflow
		pc = methods[IMM24].code;

		break;

	case RET:
		sp = (int*)*(csp--);
		bp = (int*)*(csp--);
		pc = (int*)*(csp--);
		break;

	case END:
		return 0;
	}
	goto next_opcode;
}



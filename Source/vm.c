#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"


static int globals[1024] = {1, 2, 1234, 4, 5, 0};
static int stack[1024]; // stack is not yet dynamic kinda defeats the purpose
static int * tos = stack;
static int * bp = stack;
static float * fbp;

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

	switch(OP)
	{
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
		case END:
			return 0;
	}

	goto next_opcode;
}



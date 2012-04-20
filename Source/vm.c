#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vm.h"
#include "object.h"
#include "vm_asm.h"


static void op_push(void);
static void op_add(void);
static void op_sub(void);
static void op_mul(void);
static void op_div(void);
static void op_mod(void);
static void op_sqrt(void);
static void op_pow(void);
static void op_cmp(void);
static void op_lt(void);
static void op_lte(void);
static void op_jmp(void);
static void op_mov(void);
static void op_call(void);
static void op_ret(void);
static void op_end(void);



static Object stack[1024]; // stack is not yet dynamic kinda defeats the purpose
static Object * tos = stack;
static Object * base = stack;
static Function functionTable[64];//when code is compiled this will be a list of all functions
static Function * currentFunction;
// program counter
static int * pc;

static OPCODE opType;
static int iA; // index into a register
static int iB; // index into a local variable
static int iC; // index into a local variable
static int iD; // index into global, constant or offset for jmp
static int siD;


static opTable[OP_NUM] =
{
	&op_mov

}




int vm_run(int * program)
{
	if(program == NULL)
		return 2;

	pc = program;


next_opcode:

	//Decode instruction
	opType = GETOP(*pc);
	iA = GETARG_A(*pc);
	iB = GETARG_B(*pc);
	iC = GETARG_C(*pc);
	iD = GETARG_D(*pc);
	siD = iD - (8388608);
	++pc;

	_asm
	{
		mov eax,[opTable + opType * 4];
		jmp eax;
	}




	
}


static void op_push(void){
	*(++tos) = (base)[iA]; 
}
static void op_add(void){
	base[iA].value.n = base[iB].value.n + base[iC].value.n;
}
static void op_sub(void){
	base[iA].value.n = base[iB].value.n - base[iC].value.n;
}
static void op_mul(void){
	base[iA].value.n = base[iB].value.n * base[iC].value.n;
}
static void op_div(void){
	base[iA].value.n = base[iB].value.n / base[iC].value.n;
}
static void op_mod(void){
	base[iA].value.n = base[iB].value.n % base[iC].value.n;
}
static void op_sqrt(void){
	base[iA].value.n = sqrt((double)base[iB].value.n);
}
static void op_pow(void){
	base[iA].value.n = pow((float)base[iB].value.n, base[iC].value.n);
}
static void op_cmp(void){

	if((&base[iA] != &base[iB]) && (base[iA].value.n != base[iB].value.n))
	{
		if (base[iA].type == base[iB].type == T_STR)
		{
			pc += strncmp(base[iA].value.s->string, base[iB].value.s->string, base[iA].value.s->length);//TODO: check this
		}
		else pc++;
	}
}
static void op_lt(void){
	if(base[iA].value.n >= base[iB].value.n)
		++pc;
}
static void op_lte(void){
	if(base[iA].value.n > base[iB].value.n)
		++pc;
}
static void op_jmp(void){
	pc += siD;
}
static void op_mov(void){
	base[iA] = base[iB];
}
static void op_call(void){// jumps to function and initiates stack frame
	//push return address & base pointer
	(++tos)->value.ret = pc;
	(++tos)->value.bp = base;
	
	currentFunction = functionTable + iD;
	pc = currentFunction->code;
		
	base = tos;
	tos += currentFunction->localsSz; 
}
static void op_ret(void){
	--tos;
	pc = tos->value.ret;
	--tos;
	base = tos->value.bp;
}
static void op_end(void)
{
	
}


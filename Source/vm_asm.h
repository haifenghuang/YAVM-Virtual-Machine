#ifndef VM__asm_H
#define VM__asm_H

#define ASM_POPULATE_OPTABLE __asm              \
	{						                    \
		__asm mov eax, op_push                  \
		__asm mov [opTable + OP_PUSH * 4], eax  \
		__asm mov eax, op_add				    \
		__asm mov [opTable + OP_ADD*4], eax     \
		__asm mov eax, op_sub				    \
		__asm mov [opTable + OP_SUB*4], eax     \
		__asm mov eax, op_mul				    \
		__asm mov [opTable + OP_MUL*4], eax     \
		__asm mov eax, op_div				    \
		__asm mov [opTable + OP_DIV*4], eax     \
		__asm mov eax, op_mod				    \
		__asm mov [opTable + OP_MOD*4], eax     \
		__asm mov eax, op_sqrt				    \
		__asm mov [opTable + OP_SQRT*4], eax    \
		__asm mov eax, op_pow				    \
		__asm mov [opTable + OP_POW*4], eax     \
		__asm mov eax, op_cmp				    \
		__asm mov [opTable + OP_CMP*4], eax     \
		__asm mov eax, op_lt				    \
		__asm mov [opTable + OP_LT*4], eax      \
		__asm mov eax, op_lte				    \
		__asm mov [opTable + OP_LTE*4], eax     \
		__asm mov eax, op_jmp				    \
		__asm mov [opTable + OP_JMP*4], eax     \
		__asm mov eax, op_mov				    \
		__asm mov [opTable + OP_MOV*4], eax     \
		__asm mov eax, op_call				    \
		__asm mov [opTable + OP_CALL * 4], eax  \
		__asm mov eax, op_ret					\
		__asm mov [opTable + OP_RET * 4], eax   \
		__asm mov eax, op_end				    \
		__asm mov [opTable + OP_END*4], eax     \
	}

#define ASM_VM_GOTO(op) __asm                   \
	{                                           \
		__asm mov eax, op                       \
		__asm mov eax, [opTable + eax*4]        \
		__asm jmp eax                           \
	}                                      

#endif 
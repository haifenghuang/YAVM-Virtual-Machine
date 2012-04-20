#ifndef VM__asm_H
#define VM__asm_H


#define ASM_VM_JMP(addr) __asm                  \
	{                                           \
		__asm mov eax, addr						\
		__asm jmp eax                           \
	}                                      

#endif 
#ifndef VM_H
#define VM_H	
#include "types.h"

int vm_init(int stackSz,int localsSz);
int vm_run(int * program);
int vm_shutDown();



#endif
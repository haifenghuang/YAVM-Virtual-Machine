#ifndef OPCODES_H
#define OPCODES_H

#include "types.h"

typedef struct
{
	char * opName;
	int arg1, arg2;
	int check; // how many arguments need to be verified eg. SQT only takes 1 argument so check for it is 1
}opInfo;

const opInfo opArgs[];

const char * getDebugInfo(int errorCode);
#endif
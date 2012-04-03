#ifndef VM_TYPES_H
#define VM_TYPES_H

typedef enum
{
	T_NUM,
	T_STR,
	T_BLN,
	T_OBJ,
	T_NONE,
}Type;

const char * typeStrings[];

typedef int Number;

typedef enum {B_TRUE = 1, B_FALSE = 0 } Boolean;

typedef struct {char * string; int length;}String;

typedef struct Function Function;
typedef struct Object Object;
typedef union Value Value;

struct Function
{
	int * code;
	Object * k;
	char sizeK;
	char sizeLocals;
};

union Value
{
	Number n;
	String * s;
	Boolean b;
};

struct Object
{
	Type type;
	Value value;
};



#endif
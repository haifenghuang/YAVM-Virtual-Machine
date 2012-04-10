#ifndef VM_TYPES_H
#define VM_TYPES_H

typedef enum
{
	T_NUM,
	T_STR,
	T_BLN,
	T_OBJ,
	T_FRAME,
	T_NONE,
}Type;

const char * typeStrings[];

typedef int Number;

typedef enum {B_TRUE = 1, B_FALSE = 0 } Boolean;

typedef struct {char * string; int length;}String;

typedef struct Frame Frame;
typedef struct Object Object;
typedef union Value Value;

struct Frame //activation frame
{
	int * code;
	int localsSz; // what the top of the stack should be increased by

};

union Value
{
	Number n;
	String * s;
	Boolean b;
	Frame * f;
};

struct Object
{
	Type type;
	Value value;
};



#endif
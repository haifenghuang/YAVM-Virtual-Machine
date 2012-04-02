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
typedef struct {char * string; int length;}String;
typedef enum {TRUE = 1, FALSE = 0 } Boolean;

typedef void (*OPCODE)(void);

typedef union 
{
	Number n;
	String * s;
	Boolean b;
}Value;

typedef struct 
{
	Type type;
	Value value;
}Object;



#endif
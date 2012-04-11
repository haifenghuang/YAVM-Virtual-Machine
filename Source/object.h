#ifndef VM_TYPES_H
#define VM_TYPES_H


typedef enum
{
	T_NUM,
	T_STR,
	T_BLN,
	T_OBJ,
	T_FUNC,
	T_NONE
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
	int localsSz;
};

union Value
{
	Number n;
	String * s;
	Boolean b;
	Function * f;
	int * ret; // for pushing return addresses to the stack
	Object * bp; // for pushing base pointer to stack
};

struct Object
{
	Type type;
	Value value;
};

#define type(o)(o->type)
#define valuen(o)(o->value.n)
#define values(o)(o->value.s)
#define valueb(o)(o->value.b)
#define valuef(o)(o->value.f)
#define valueret(o)(o->value.ret)
#define valuebp(o)(o->value.bp)

#endif
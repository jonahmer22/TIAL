#ifndef MAIN_H
#define MAIN_H

#include "arena.h"

#include <stdlib.h>
#include <stdbool.h>

typedef enum{
	INSTR_PRINT,		// read the next instruction as an index to data, then print the value
	INSTR_VALUE,		// maps to an index in Bytecode->data, which is a pointer to a value
	INSTR_EXIT		// ends the program
} Instr;

typedef enum{
	TYPE_NUM,
	TYPE_STRING,
	TYPE_BOOL,
	TYPE_DNE
} ValueType;

typedef struct Value{
	ValueType type;
	union{
		double _num;
		char *_string;
		bool _bool;
	} as;
} Value;

typedef struct Bytecode{
	// basic arena allocated list of instructions
	Instr *start;
	Instr *end;	// one past last
	size_t length;

	// data associated with this bytecode
	Value *data;	// a list of values that the bytecode can use
	
	// where in the program we are
	size_t ip;
} Bytecode;

#endif

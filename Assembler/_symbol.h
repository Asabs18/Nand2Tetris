#pragma once
#include "debug.h"
#include "symbol.h"
#include "uthash.h"

///_symbol.h contains all UI functions for the symbolTable_t struct///
///This struct contains an id(serves as a key) a name () 

#define STARTSIZE 50

//a struct that represents one symbol in the symbol table
typedef struct _symbol_t{
    const char* key; //key(char* not char[] so memory is layed out in a different way. internal: * vs external: [])
    void* value; //value
    UT_hash_handle hh; //var makes this hashable
}symbol_t;

//the data struct for a symbol table
typedef struct _symbolTable_t {
    symbol_t* table; //table structure
}symbolTable_t;

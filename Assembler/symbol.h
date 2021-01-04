#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "uthash.h"

///symbol.h contains all functions for symbol_t and all internal functions for symbolTable_t///
///symbol_t represents one pair out of a undefined number in the symbol table, each having a key and a value and a hash handle///
///the _symbolTable_t* struct is referenced here but declared in _symbol.h to make the data structure fully abstract//


typedef struct _symbolTable_t* symbolTable_p;
typedef struct _symbol_t* symbol_p;

typedef struct predef{
	char* name;
	void* val;
}predef_t;

//symbolTable_t table;

//function definitions for all symbol table functions
//Creates a blank symbol table and fills it with all basic predef commands
symbolTable_p createSymbolTable();
//adds a value to the passed in symbol table
bool insert(symbolTable_p table, const char * key, void* value);
//this prints the symbol table to the file output for debugging
bool printHash(symbolTable_p table, FILE* output, const char * key);
//frees symbol table memory
void destroySymbolTable(symbolTable_p table);
//gets the size of the passed in symbol table(to make symbolTable_t fully abstract)
int getSize(symbolTable_p table);
//Checks if a symbol meets all of the params
bool isStringValidSymbol(const char* string);
//gets the key from the passed symbol_p
symbol_p getVal(symbolTable_p table, const char* key); 
//sets a value in a symbol
void setValue(symbolTable_p table, symbol_p symb, void* value);
int getSize(symbolTable_p table);
symbol_p createSymbol(const char * key);
void destroySymbol(symbol_p symb);
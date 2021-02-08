#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "assemble.h"
#include "symbol.h"
#include "_symbol.h"

///This file includes all declarations for the definitions in the symbol.h file///
///These functions are all for the symbol_t struct or the internal symbolTable_t struct///

//frees all of the passed in memory
void destroySymbolTable(symbolTable_p table) {
	symbol_p s;
	symbol_p tmp;
	HASH_ITER(hh, table->table, s, tmp) {
		HASH_DEL(table->table, s);
		destroySymbol(s);
	}
	free(table);
}

void destroySymbol(symbol_p symb) {
	free(symb);
}

//adds an element to the symbol table
bool insert(symbolTable_p table, const char* key, void* value) {
	//Checks if the asked for symbol is already in the table
	bool output = false;
	symbol_t* symb = (symbol_t*)-1;
	symbolTable_t* tbl = table;
	if (tbl != NULL) {
		HASH_FIND_PTR(tbl->table, key, symb);
	}
	//If its not, create a new symbol with the params and add it
	if (symb == NULL) {
		symb = createSymbol(key);
		setValue(table, symb, value);
		output = true;
	}
	//return true if its added in and false if it exists
	return output;
}

//prints the whole table for debugging purposes 
bool printHash(symbolTable_p table, FILE* output, const char* key) {
	symbol_p symb = getVal(table, key);
	int val = *((int*)symb->value);
	fprintf(output, "Your Key is %s. Your Value is %d (%x)\n", symb->key, val, val);
	return true;
}

//creates a basic symbol table, only will have predef symbols in it to start
symbolTable_p createSymbolTable() {
	//reserves the memory for the created, empty symbol table
	symbolTable_p table = malloc(sizeof(symbolTable_t));
	assert(table != NULL);
	table->table = NULL;
	return table;
}

#define MAXDIGIT 10


//Constants must be non - negative and are written in decimal
//notation.A user - defined symbol can be any sequence of letters, digits, underscore(_),
//dot(.), dollar sign($), and colon(:) that does not begin with a digit

bool isStringValidSymbol(const char* string) {
	//Sets return value to true
	bool isValid = true;
	//Checks if the first digit is a number and if so returns false
	if (isdigit(string[0])) {
		isValid = false;
	}
	else {
		//Enters a for loop that looks at each part of string
		for (size_t i = 0; i < strlen(string); i++) {
			//Checks if each char in string is one of the accepted values
			if (isalnum(string[i]) || string[i] == '_' || string[i] == '$' || string[i] == '.' || string[i] == ':' || isdigit(string[i])) {
				//if so continues
				continue;
			}
			else {
				//Otherwise returns false
				isValid = false;
				break;
			}
		}
	}
	//Return the value that has been possibly changed through the function
	return isValid;
}
//Creates an empty symbol
symbol_p createSymbol(const char* key) {
	//TODO: LEAKING MEMORY
	symbol_t* symbol = malloc(sizeof(symbol_t));
	assert(symbol);
	symbol->key = key;
	return symbol;
}
//returns the key from a symbol
symbol_p getVal(symbolTable_p table, const char* key) {
	//If there is a key return it but if there is not return an err
	if (key == NULL) {
		return NULL;
	}
	symbol_p output = createSymbol(key);
	HASH_FIND_STR(table->table, key, output);
	//assert(output != NULL);
	return output;
}
//sets the value in the symbol
void setValue(symbolTable_p table, symbol_p symb, void* value) {
	assert(table != NULL);
	if (symb != NULL) {
		symb->value = value;
		HASH_ADD_STR(table->table, key, symb);
	}
}
//returns a symbols tables size to make the symbol table fully abstract
int getSize(symbolTable_p table) {
	return HASH_COUNT(table->table);
}
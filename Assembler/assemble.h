#pragma once
#include <stdbool.h>
#include "debug.h"
#include "symbol.h"

///This file contains the cmp, dst, jmp data structs which contains hex values for all commands for each division of the c-command///
///This file also has the command_t struct which has a char* with the current line being read///
///command_t also has the current line number the program is on and the command type i.e A, C or L command///
///This file also contains the function definitions for functions that handle parse or handling commands///

//#define FULLCOMMENT NULL
#if !defined(FULLCOMMENT)
#	define FULLCOMMENT "//skip"
#	define CHECK_SKIP_COMMAND(command) (strcmp((command), "//skip") == 0)
#else
#	define FULLCOMMENT NULL
#	define CHECK_SKIP_COMMAND(command) ((command) == NULL)
#endif

#define DESTOPTIONS 9
#define COMPOPTIONS 29
#define JUMPOPTIOND 9
#define REGSTRLEN 5

typedef enum commandType_t { A, C, L, N } commandType_t;
//plus/minus refers to one
//All possible commands for cmp dst jmp respectively //TODO: add high order bit
typedef enum comp_e { nullcomp = 0x0, zero = 0xA80, one = 0xFC0, negOne = 0xE80, Dcomp = 0x300, Acomp = 0xC00, notD = 340, notA = 0xC40, negD = 0x3C0, negA = 0xCC0, Dplus = 0x7C0, Aplus = 0xDC0, Dminus = 0x380, Aminus = 0xC80, DplusA = 0x80, DminusA = 0x4C0, AminusD = 0x1C0, DandA = 0x0, DorA = 0x540, Mcomp = 0x1C00, notM = 0x1C40, negM = 0x1CC0, Mplus = 0x1DC0, Mminus = 0x1C80, DplusM = 0x1080, DminusM = 0x14C0, MminusD = 0x11C0, DandM = 0x1000, DorM = 0x1540, numComps = 29 } comp_t; //6 places
typedef enum dest_e { nulldest = 0x0, Mdest = 0x8, Ddest = 0x10, MD = 0x18, Adest = 0x20, AM = 0x28, AD = 0x30, AMD = 0x38, numDests = 8 } dest_t;
typedef enum jump_e { nulljump = 0x0, JGT = 0x1, JEQ = 0x2, JGE = 0x3, JLT = 0x4, JNE = 0x5, JLE = 0x6, JMP = 0x7, numJumps } jump_t; //TODO: clean up enum naming

//Data structure that represents a given assembly language command
typedef struct {
	commandType_t type; // A, C or L command
	char* command; // string of the read in command
}command_t;

//each element of the c command
typedef struct {
	comp_t comp; // needed
	dest_t dest; // optional
	jump_t jump; // optional
}cInstruct_t;

typedef struct {
	cInstruct_t C;
	int A;
}Instruction_t;

typedef struct {
	command_t* command;
	int addresses;
}AR_t;

///----------------SYMBOL--TABLE--HELPER--FUNCTIONS----------------///
//Adds all predef symbols to general symbol table
symbolTable_p addPredefSymbs(symbolTable_p table);
//adds values for each C-Command field respectively 
symbolTable_p fillJumpTable(symbolTable_p jumpTable, jump_t vals[]);
symbolTable_p fillDestTable(symbolTable_p destTable, dest_t vals[]);
symbolTable_p fillCompTable(symbolTable_p compTable, comp_t vals[]);


///----------------HELPER--FUNCTIONS-------------------------------///
//checks to see if a value(char*) is a num or not
bool isNum(char* command);
//Opens a file for reading
FILE* openFile(const char* readFrom);
//frees the memory for the passed in command_t
void destroyCommand(command_t* command);
//Checks if there are more lines in the file or not
bool areThereMoreCommands(FILE* readFrom);
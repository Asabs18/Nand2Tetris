#pragma once

#include <stdbool.h>
#include "assemble.h"
#include "debug.h"
#include "symbol.h"

///---------------PARSER-----------------///
//Calls comp, dest, jump helper functions based on the passed in command_t
cInstruct_t parseCInstruction(command_t* currCommand);
//finds and returns the value of the dest part of the C-Command
cInstruct_t dest(command_t* currCommand, cInstruct_t instruction, int endAt);
//finds and returns the value of the comp part of the C-Command
cInstruct_t comp(command_t* currCommand, cInstruct_t instruction, int Ceq, int Csc);
//finds and returns the value of the jump part of the C-Command
cInstruct_t jump(command_t* currCommand, cInstruct_t instruction, int startAt);
//Calls the Parse A, C and L instructions based on Pass and command type
Instruction_t parse(command_t* currCommand, int pass, symbolTable_p table, int memAddress);
//Parses the A instructions
int parseAInstruction(command_t* currCommand, symbolTable_p symbolTable, int memAddress);
//Parses the L Instructions
bool parseLInstruction(command_t* currCommand, symbolTable_p table, int memAddress);
//adds values for each C-Command field respectively 
static symbolTable_p fillJumpTable(symbolTable_p jumpTable, jump_t vals[]);
static symbolTable_p fillDestTable(symbolTable_p destTable, dest_t vals[]);
static symbolTable_p fillCompTable(symbolTable_p compTable, comp_t vals[]);
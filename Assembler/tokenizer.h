#pragma once
#include <stdbool.h>
#include "assemble.h"
#include "debug.h"
#include "symbol.h"


///----------------TOKENIZER--------------///
//Moves to the next line in a file, different functions for each pass
AR_t* advancePass1(command_t* currCommand, FILE* readFrom);
AR_t* advancePass2(command_t* currCommand, FILE* readFrom);
//Gets the command type of a command_t->command(char*)
command_t* commandType(command_t* currCommand);
//Updates each field of a command_t i.e LineNum, command, commandType
command_t* updateCommand(command_t* currCommand, FILE* readFrom);
//Reads a command from the passed in file(does not close file so it does not restart reading)
char* createCommand(FILE* readFrom);
//gets rid of all whitespace in a command(char*)
char* stripWhiteSpace(char* command);
//Checks if the current command had a comment, if so calls helper functions to remove it
char* checkComments(char* command, size_t size);
//removes comments from a command
char* stripComments(char* command, size_t i);
bool resetAR_t(AR_t* advanceOutput);
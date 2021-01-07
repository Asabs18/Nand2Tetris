#pragma once

#include <stdbool.h>
#include "assemble.h"
#include "debug.h"
#include "symbol.h"

///--------------CODE-GENERATOR------------///
//Overall wrapper function that takes a command(A or C) and adds its correct binary output to a output.hack file
bool GenerateCode(Instruction_t* instruct, FILE* fp);
//takes a binary output converts to Ascii and writes to the output file
bool produceOutput(uint16_t binVal, FILE* fp); //Not sure abt param val
//Takes a C-Command and outputs its corresponding Binary value
bool generateC_Command(cInstruct_t command, FILE* fp);
//takes a A-Command and outputs it corresponding Binary value
bool generateA_Command(int command, FILE* fp);
//Takes a int value and converts it to an ASCII binary string
char* intToAscii(int intIn);
//Opens a file and returns the pointer
FILE* openOutputFile(char* fileName);
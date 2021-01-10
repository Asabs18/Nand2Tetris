#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "munit.h"
#include "parser.h"
#include "symbol.h"
#include "_symbol.h"

#define MAXSIZE 100
#define EMPTYVAL 0

/*
PARSING THE C-INSTRUCTION:
a command_t* will be passed into parseCInstruction() containing the curr command
A cInstruct_t will be created in the function parseCInstruction()
This will contain 3 empty enum values for cmp, dst, jmp
parseCInstriction() will go on to read the line and do simple parsing
to determine if the instruction contains jump and dest fields
if these fields are not in the curr instruction they will be set to the
null value, otherwise they will be passed of to the respective functions
to parse each part

each helper function(cmp,dst,jmp) will look for key values(=,;) to
separate the currInstruction into its parts. They will then copy the
correct part of this line into a new char*. This char* will then be
checked if it is in the correct enum. if not the field will be set
to an error code and returned. if so it will be set to the correct
enum and returned. this value is now considered parsed and will
be assumed to have to correct numerical value for the rest of the
program. enums are represented with hex values for the moment so
the translation from hex to binary will be the only remaining issue for
parsed commands
*/

static symbolTable_p fillDestTable(symbolTable_p destTable, dest_t vals[]) {
	//Adds all real values for a Dest command
	insert(destTable, "null", &vals[0]);
	insert(destTable, "M", &vals[1]);
	insert(destTable, "D", &vals[2]);
	insert(destTable, "MD", &vals[3]);
	insert(destTable, "A", &vals[4]);
	insert(destTable, "AM", &vals[5]);
	insert(destTable, "AD", &vals[6]);
	insert(destTable, "AMD", &vals[7]);
	return destTable;
}

cInstruct_t dest(command_t* currCommand, cInstruct_t instruction, int endAt) {
	static dest_t vals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	//creates a symbol table for dest values
	symbolTable_p destTable = createSymbolTable();
	//fills the dest symbol table
	destTable = fillDestTable(destTable, vals);
	char dest[MAXSIZE];
	int index = 0;
	//goes from 0 - endAt in command and putting each char in a buffer for the dest part of the command
	for (int j = 0; j < endAt; j++) {
		dest[j] = currCommand->command[j];
		index++;
	}
	dest[index] = '\0';
	//if the past in value is in the dest table put the value in instruction.dest
	if (getVal(destTable, dest) != NULL) {
		symbol_p output = getVal(destTable, dest);
		assert(output != NULL);
		instruction.dest = *((int*)output->value);
	}
	else {
		instruction.dest = nulldest;
	}

	return instruction;
}

static symbolTable_p fillCompTable(symbolTable_p compTable, comp_t vals[]) {
	//fills all the predefined values of the Comp Table
	insert(compTable, "0", &vals[0]);
	insert(compTable, "1", &vals[1]);
	insert(compTable, "-1", &vals[2]);
	insert(compTable, "D", &vals[3]);
	insert(compTable, "A", &vals[4]);
	insert(compTable, "!D", &vals[5]);
	insert(compTable, "!A", &vals[6]);
	insert(compTable, "-D", &vals[7]);
	insert(compTable, "-A", &vals[8]);
	insert(compTable, "D+1", &vals[9]);
	insert(compTable, "A+1", &vals[10]);
	insert(compTable, "D-1", &vals[11]);
	insert(compTable, "A-1", &vals[12]);
	insert(compTable, "D+A", &vals[13]);
	insert(compTable, "D-A", &vals[14]);
	insert(compTable, "A-D", &vals[15]);
	insert(compTable, "D&A", &vals[16]);
	insert(compTable, "D|A", &vals[17]);
	insert(compTable, "M", &vals[18]);
	insert(compTable, "!M", &vals[19]);
	insert(compTable, "-M", &vals[20]);
	insert(compTable, "M+1", &vals[21]);
	insert(compTable, "M-1", &vals[22]);
	insert(compTable, "D+M", &vals[23]);
	insert(compTable, "D-M", &vals[24]);
	insert(compTable, "M-D", &vals[25]);
	insert(compTable, "D&M", &vals[26]);
	insert(compTable, "D|M", &vals[27]);
	insert(compTable, "null", &vals[28]);
	return compTable;
}

cInstruct_t comp(command_t* currCommand, cInstruct_t instruction, int Ceq, int Csc) {
	//creates and adds correct predef values to comp table
	static comp_t vals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
				Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
				negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, vals);
	char comp[MAXSIZE];
	//creates a start and end variable for when to start and stop looking for comp values in the instruction
	int start = 0;
	int end = strlen(currCommand->command);
	//if there are passed in start and end values use those, otherwise parse the whole instruction
	if (Ceq > 0) {
		start = Ceq + 1;
	}
	if (Csc > 0) {
		end = Csc;
	}
	//parse instruction to find comp components 
	int index = 0;
	for (int i = start; i < end; i++) {
		comp[index] = currCommand->command[i];
		index++;
	}
	comp[index] = '\0';
	//get value from comp table and return it
	if (getVal(compTable, comp) != NULL) {
		symbol_p output = getVal(compTable, comp);
		assert(output != NULL);
		instruction.comp = *((int*)output->value);
	}

	return instruction;
}

static symbolTable_p fillJumpTable(symbolTable_p jumpTable, jump_t vals[]) {
	//fills jump table with predefined values
	insert(jumpTable, "null", &vals[0]);
	insert(jumpTable, "JGT", &vals[1]);
	insert(jumpTable, "JEQ", &vals[2]);
	insert(jumpTable, "JGE", &vals[3]);
	insert(jumpTable, "JLT", &vals[4]);
	insert(jumpTable, "JNE", &vals[5]);
	insert(jumpTable, "JLE", &vals[6]);
	insert(jumpTable, "JMP", &vals[7]);
	return jumpTable;
}


cInstruct_t jump(command_t* currCommand, cInstruct_t instruction, int startAt) {
	//creates and adds predefined symbols to the jump table
	jump_t vals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, vals);
	char jump[MAXSIZE];
	int index = 0;
	//parse the instruction from startAt to the end of the instruction to look for jump elements
	for (size_t j = startAt; j < strlen(currCommand->command); j++) {
		jump[index] = currCommand->command[j];
		index++;
	}
	jump[index] = '\0';
	//get correct jump value and return it
	if (getVal(jumpTable, jump) != NULL) {
		symbol_p output = getVal(jumpTable, jump);
		assert(output != NULL);
		instruction.jump = *((int*)output->value);
	}
	return instruction;
}
cInstruct_t parseCInstruction(command_t* currCommand) {
	cInstruct_t instruction = { nullcomp, nulldest, nulljump };
	//vars used to start index values of = and ; to avoid double parsing the instruction
	int Ceq = 0;
	int Csc = 0;
	//parse instruction for key values
	for (size_t i = 0; i < strlen(currCommand->command); i++) {
		//if you find an equal sign, parse the dest part of C instruction
		if (currCommand->command[i] == '=') {
			instruction = dest(currCommand, instruction, i);
			Ceq = i;
		}
		//if you find a semicolon parse the jump part of the C instruction
		if (currCommand->command[i] == ';') {
			instruction = jump(currCommand, instruction, i + 1);
			Csc = i;
		}
	}
	//always parse the comp because it is always there
	instruction = comp(currCommand, instruction, Ceq, Csc);

	return instruction;
}
bool parseLInstruction(command_t* currCommand, symbolTable_p table, int memAddress) {
	assert(currCommand->type == L);
	char cmd[MAXSIZE];
	int Cmdlen = strlen(currCommand->command);
	//parse out the parenthesis in the L instruction 
	if (currCommand->command[0] == '(' && currCommand->command[Cmdlen - 1] == ')') {
		for (int i = 1; i < Cmdlen; i++) {
			cmd[i - 1] = currCommand->command[i];
		}
	}
	cmd[Cmdlen - 2] = '\0';
	currCommand->command = _strdup((char*)cmd);
	int* mem = malloc(sizeof(memAddress));
	*mem = memAddress;
	//if the command if valid 
	if (isNum(currCommand->command) == false) {
		//otherwise check if the string is a valid symbol, if so add to the symbol table and set output to -1
		if (isStringValidSymbol(currCommand->command)) {
			//if the command is not in the table already
			if (getVal(table, currCommand->command) == NULL) {
				//add it to the table with the current address
				insert(table, currCommand->command, (void*)mem);
				return true;
			}
		}
	}
	return false;
}


bool isNum(char* command) {
	//loops through a string and makes sure each element is a digit
	for (size_t i = 0; i < strlen(command); i++) {
		if (isdigit(command[i]) == false) {
			return false;
		}
	}
	return true;
}

#define MAXINTSIZE 32767
//Returns a positive decimal val if the command is a int. if the command is a symbol adds to symbol table then returns -1 if an invalid input is given -2 is returned
int parseAInstruction(command_t* currCommand, symbolTable_p symbolTable, int memAddress) {
	int val = 0;
	char cmd[MAXSIZE];
	int Cmdlen = strlen(currCommand->command);
	//checks if the command is an A instruct
	if (currCommand->command[0] == '@') {
		//copies the string to a new var without the leading @
		for (int i = 1; i < Cmdlen; i++) {
			cmd[i - 1] = currCommand->command[i];
		}
		cmd[Cmdlen - 1] = '\0';
		currCommand->command = _strdup((char*)cmd);
		int* mem = malloc(sizeof(memAddress));
		*mem = memAddress;
		//checks if the string is a number, if so sets the output to the number version of the string
		int number = atoi(cmd);
		if (number == 0 && strcmp(cmd, "0") != 0) {
			number = -1;
		}
		if (isNum(cmd) && number >= 0 && number <= MAXINTSIZE) {
			val = atoi(cmd);
		}
		//if the command is in the table get the value back and return it
		else if (getVal(symbolTable, currCommand->command) != NULL) {
			symbol_p symb = getVal(symbolTable, currCommand->command);
			val = *((int*)symb->value);
		}
		//otherwise add it to the value
		else if (isStringValidSymbol(currCommand->command) == true) {
			insert(symbolTable, currCommand->command, mem);
			//convert the value to a negative to tell the main loop that a value was added
			val = *mem;
			val *= -1;
			val -= 1;
		}
	}
	return val;
}


Instruction_t parse(command_t* currCommand, int pass, symbolTable_p table, int memAddress) {
	cInstruct_t temp = { nullcomp, nulldest, nulljump };
	Instruction_t cmdVal = { temp, -1 };
	if (currCommand->command[strlen(currCommand->command) - 1] == '\n') {
		currCommand->command[strlen(currCommand->command) - 1] = '\0';
	}
	//if its the first pass only parse L instructions
	if (pass == 1) {
		if (currCommand->type == L) {
			if (parseLInstruction(currCommand, table, memAddress)) {
				cmdVal.A = -2;
			}
		}
	}
	//on the second pass ignore L instructions
	else {
		if (currCommand->type == A) {
			cmdVal.A = parseAInstruction(currCommand, table, memAddress);
		}
		else if (currCommand->type == C) {
			cmdVal.C = parseCInstruction(currCommand);
		}
	}
	return cmdVal;
}

#define OFFBY 7
#define REGNUM 16
#define NAMELEN 2
//Adds predefined symbols to the symbol table
symbolTable_p addPredefSymbs(symbolTable_p table) {
	static int values[] = { 16384, 24576, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	//TODO: Add loop for registers
	insert(table, "SCREEN", &values[0]);
	insert(table, "KBD", &values[1]);
	insert(table, "SP", &values[2]);
	insert(table, "LCL", &values[3]);
	insert(table, "ARG", &values[4]);
	insert(table, "THIS", &values[5]);
	insert(table, "THAT", &values[6]);
	insert(table, "R0", &values[7]);
	insert(table, "R1", &values[8]);
	insert(table, "R2", &values[9]);
	insert(table, "R3", &values[10]);
	insert(table, "R4", &values[11]);
	insert(table, "R5", &values[12]);
	insert(table, "R6", &values[13]);
	insert(table, "R7", &values[14]);
	insert(table, "R8", &values[15]);
	insert(table, "R9", &values[6]);
	insert(table, "R10", &values[17]);
	insert(table, "R11", &values[18]);
	insert(table, "R12", &values[19]);
	insert(table, "R13", &values[20]);
	insert(table, "R14", &values[21]);
	insert(table, "R15", &values[22]);
	return table;
}

void destroyCommand(command_t* command) {
	free(command->command);
	//free(command); //TODO: come back to 
}
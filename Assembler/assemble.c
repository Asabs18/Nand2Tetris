#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "assemble.h"
#include "symbol.h"
#include "_symbol.h"

#define MAXSIZE 30
#define EMPTYVAL 0

///this file contains all function declarations that have to do with parsing or handling the command/// 

FILE* openFile(const char* readFrom) {
	FILE* file;
	fopen_s(&file, readFrom, "r");
	assert(file != NULL);
	return file;
}

char* createCommand(FILE* file) {
	static char command[MAXSIZE];
	//gets the next command and sets it to command
	fgets(command, sizeof(command), file);
	return command;
}

char* stripComments(char* command, int i) {
	//removes comments from the string
	static char newCommand[MAXSIZE];
	assert(i < MAXSIZE);
	//takes everything from a line except the comment 
	strncpy_s((char*)newCommand, sizeof(newCommand), command, i);
	//puts the new line character at the end of the string
	newCommand[i] = '\n';
	//removes any white space before the newline
	for (int j = i; j > 0; j--) {
		if (newCommand[j] == ' ') {
			newCommand[j] = '\n';
			i = j;
			break;
		}
	}
	//copies the new string over without white space
	assert(i < (MAXSIZE - 1));
	newCommand[i + 1] = '\0'; //TODO: Stop buffer overrun
	return (char*)newCommand;
}

char* checkComments(char* command, int size) {
	//Checks if the currCommand is or has a comment
	for (int i = 0; i < size; i++) {
		//creates a pair of chars that go through the string and find back to back '/'
		char currChar = command[i];
		char nextChar = command[i + 1];
		if (currChar == '/' && nextChar == '/') {
			//if they are at the start of the line, the line has no code so it gets skipped
			if (i == 0) {
				return FULLCOMMENT;
			}
			//Otherwise set size to how far i got which is how much valid code there is on a line. (there is never a need for code after a comment on the same line)
			else {
				return stripComments(command, i);
			}
		}
	}
	return command;
}

char* stripWhiteSpace(char* command) {
	char newCommand[MAXSIZE];
	int newCommandIndex = 0;
	for (size_t i = 0; i < strlen(command); i++) {
		if (command[i] != ' ') {
			newCommand[newCommandIndex] = command[i];
			newCommandIndex++;
		}
	}
	newCommand[newCommandIndex] = '\0';
	command = strdup(newCommand);
	return command;
}

//moves the current command to the next valid line
command_t* advancePass1(command_t* currCommand, FILE* readFrom) {
	//runs until the return statement is hit in the loop
	currCommand = updateCommand(currCommand, readFrom);
	currCommand->command = stripWhiteSpace(currCommand->command);
	while (true) {
		//if the current line is a comment get the next line
		while (currCommand->command == NULL || strcmp(currCommand->command, "//skip") == 0) {
			currCommand = updateCommand(currCommand, readFrom);
		}
		//if the command is an L command return it
		if (currCommand->type == L) {
			return currCommand;
		}
		//Otherwise get the next line
		else {
			currCommand = updateCommand(currCommand, readFrom);
		}
	}
}

//moves the current command to the next valid line
command_t* advancePass2(command_t* currCommand, FILE* readFrom) {
	currCommand = updateCommand(currCommand, readFrom);
	currCommand->command = stripWhiteSpace(currCommand->command);
	while (true) {
		//get the next line if the current line is a comment
		while (currCommand->command == NULL || strcmp(currCommand->command, "//skip") == 0) {
			currCommand = updateCommand(currCommand, readFrom);
		}
		//return everything that is not an L command
		if (currCommand->type != L) {
			return currCommand;
		}
		//If the command is an L command get the next line
		else {
			currCommand = updateCommand(currCommand, readFrom);
		}
	}
}


command_t* updateCommand(command_t* currCommand, FILE* readFrom) {
	//gets a new command from the read file
	currCommand->command = createCommand(readFrom);
	//gets the length of the command
	int cmdLen = strlen(currCommand->command);
	//updates the line number
	currCommand->lineNumber++;
	//copies the command into a command_t data structure
	if (currCommand->command != NULL) {
		//free(currCommand->command);
	}
	currCommand->command = _strdup(checkComments(currCommand->command, cmdLen));
	//gets the command type of the current command
	currCommand = commandType(currCommand);
	//returns the new command
	return currCommand;
}

//returns the command type of the current command, A, C or L command 
command_t* commandType(command_t* currCommand) {
	int size;
	//TODO: Make the if statement code work. BEFORE USING NULL AS A FULL LINE COMMENT REPLACEMENT
	//if (currCommand->command == NULL) {
		//size = 1;
	//}
	//else {
	size = strlen(currCommand->command);
	//}
	int lastPlace = 1;
	if (currCommand->command[size - lastPlace] == '\n') {
		lastPlace++;
	}
	if (currCommand->command[0] == '(' && currCommand->command[size - lastPlace] == ')') {
		currCommand->type = L;
	}
	else if (currCommand->command[0] == '@') {
		currCommand->type = A;
	}
	else {
		currCommand->type = C;
	}
	return currCommand;
}
//checks if there are more commands in the file
bool areThereMoreCommands(FILE* readFrom) { //TODO: Switch to ternary operator
	bool isFileEnd = false;
	//feof() returns 0 is there are still lines left in a file
	if (feof(readFrom) != 0) {
		isFileEnd = true;
	}
	return isFileEnd;
}

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

symbolTable_p fillDestTable(symbolTable_p destTable, dest_t vals[]) {
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

cInstruct_t dest(command_t* currCommand, cInstruct_t instruction, int i) {
	static dest_t vals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, vals);
	char dest[MAXSIZE];
	int index = 0;
	for (int j = 0; j < i; j++) {
		dest[j] = currCommand->command[j];
		index++;
	}
	dest[index] = '\0';
	if (getVal(destTable, dest) != NULL) {
		symbol_p output = getVal(destTable, dest);
		munit_assert(output != NULL);
		instruction.dest = *((int*)output->value);
	}

	return instruction;
}

//TODO: ASK ABOUT NAME VS NUMBER NEEDED
symbolTable_p fillCompTable(symbolTable_p compTable, comp_t vals[]) {
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

cInstruct_t comp(command_t* currCommand, cInstruct_t instruction) {
	static comp_t vals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
				Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
				negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, vals);
	char comp[MAXSIZE];
	int start = 0;
	int end = strlen(currCommand->command);
	if (instruction.dest != nulldest) {
		for (size_t i = 0; i < strlen(currCommand->command); i++) {
			if (currCommand->command[i] == '=') {
				start = i + 1;
				break;
			}
		}
	}
	if (instruction.jump != nulljump) {
		for (size_t i = 0; i < strlen(currCommand->command); i++) {
			if (currCommand->command[i] == ';') {
				end = i;
				break;
			}
		}
	}
	int index = 0;
	for (int i = start; i < end; i++) {
		comp[index] = currCommand->command[i];
		index++;
	}
	comp[index] = '\0';

	if (getVal(compTable, comp) != NULL) {
		symbol_p output = getVal(compTable, comp);
		assert(output != NULL);
		instruction.comp = *((int*)output->value);
	}

	return instruction;
}

symbolTable_p fillJumpTable(symbolTable_p jumpTable, jump_t vals[]) {
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


cInstruct_t jump(command_t* currCommand, cInstruct_t instruction, int i) {
	jump_t vals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, vals); //TODO: change name from create
	//symbol_p put = getVal(jumpTable, "JMP");
	char jump[MAXSIZE];
	int index = 0;
	for (size_t j = i; j < strlen(currCommand->command); j++) {
		jump[index] = currCommand->command[j];
		index++;
	}
	jump[index] = '\0';
	if (getVal(jumpTable, jump) != NULL) {
		symbol_p output = getVal(jumpTable, jump);
		assert(output != NULL);
		instruction.jump = *((int*)output->value);
	}
	return instruction;
}
cInstruct_t parseCInstruction(command_t* currCommand) {
	cInstruct_t instruction = { nullcomp, nulldest, nulljump };
	for (size_t i = 0; i < strlen(currCommand->command); i++) {
		if (currCommand->command[i] == '=') {
			instruction = dest(currCommand, instruction, i);
		}
		if (currCommand->command[i] == ';') {
			instruction = jump(currCommand, instruction, i + 1);
		}
	}
	instruction = comp(currCommand, instruction);

	return instruction;
}
void parseLInstruction(command_t* currCommand, symbolTable_p table) {
	assert(currCommand->type == L);
	char cmd[MAXSIZE];
	int Cmdlen = strlen(currCommand->command);
	if (currCommand->command[0] == '(' && currCommand->command[Cmdlen] == ')') {
		for (int i = 1; i < Cmdlen; i++) {
			cmd[i - 1] = currCommand->command[i];
		}
		cmd[Cmdlen] = '\0';
	}
	if (isNum(cmd) == false) {
		//otherwise check if the string is a valid symbol, if so add to the symbol table and set output to -1
		if (isStringValidSymbol(cmd)) {
			if (getVal(table, (const char*)cmd) == NULL) {
				insert(table, cmd, EMPTYVAL); //TODO: change EMPTYVAL to actual ROM adress
			}
		}
	}
}


bool isNum(char* command) {
	for (size_t i = 0; i < strlen(command); i++) {
		if (isdigit(command[i]) == false) {
			return false;
		}
	}
	return true;
}

//Returns a positive decimal val if the command is a int. if the command is a symbol adds to symbol table then returns -1 if an invalid input is given -2 is returned
int parseAInstruction(command_t* currCommand, symbolTable_p symbolTable) {
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
		//checks if the string is a number, if so sets the output to the number version of the string
		if (isNum(cmd)) {
			val = atoi(cmd);
		}
		else {
			symbol_p symb = getVal(symbolTable, (const char*)cmd);
			val = *((int*)symb->value);
		}
	}
	return val;
}


Instruction_t parse(command_t* currCommand, int pass, symbolTable_p table) {
	cInstruct_t temp = { nullcomp, nulldest, nulljump };
	Instruction_t cmdVal = { temp, 0 };
	if (pass == 1) {
		if (currCommand->type == L) {
			parseLInstruction(currCommand, table);
		}
	}
	else {
		if (currCommand->type == A) {
			cmdVal.A = parseAInstruction(currCommand, table);
		}
		else if (currCommand->type == C) {
			cmdVal.C = parseCInstruction(currCommand);
		}
	}
	return cmdVal;
}

//Adds predefined symbols to the symbol table
symbolTable_p addPredefSymbs(symbolTable_p table, int values[]) {
	char name[REGSTRLEN];
	for (int i = 0; i < 16; i++) {
		sprintf_s(name, REGSTRLEN, "R%d", i);
		insert(table, name, &i);
	}
	insert(table, "SCREEN", &values[0]);
	insert(table, "KBD", &values[1]);
	insert(table, "SP", &values[2]);
	insert(table, "LCL", &values[3]);
	insert(table, "ARG", &values[4]);
	insert(table, "THIS", &values[5]);
	insert(table, "THAT", &values[6]);
	return table;
}

void destroyCommand(command_t* command) {
	free(command->command);
	//free(command); //TODO: come back to 
}

//CODE--GEN//
bool GenerateCode(Instruction_t* instruct, FILE* fp) {
	if (instruct->A != 0) {
		generateA_Command(instruct->A, fp);
	}
	else if (instruct->C.comp != nullcomp) {
		generateC_Command(instruct->C, fp);
	}
	else {
		return false;
	}
	return true;
}

bool produceOutput(uint16_t binVal, FILE* fp) {
	char* output = intToAscii(binVal);
	char* fileName = "output.hack";
	if (strlen(output) < 16) {
		for (size_t i = 0; i < (16 - strlen(output)); i++) {
			fprintf(fp, "0");
		}
	}
	fprintf(fp, "%s\n", output);
	return true;
}

bool generateC_Command(cInstruct_t command, FILE* fp) {
	uint16_t startVal = 0xE000;
	uint16_t output = startVal | (uint16_t)command.comp;
	output |= (uint16_t)command.dest;
	output |= (uint16_t)command.jump;
	return produceOutput(output, fp);
}

#define SIXTEEN_CHAR_OFF 0x7FFF
bool generateA_Command(int command, FILE* fp) {
	uint16_t output = (uint16_t)command & SIXTEEN_CHAR_OFF;
	return produceOutput(output, fp);;
}

char* intToAscii(int intIn) {
	static char buffer[MAXSIZE];
	_itoa_s(intIn, buffer, MAXSIZE, 2);
	return buffer;
}

FILE* openOutputFile(char* fileName) {
	FILE* fp;
	errno_t err = fopen_s(&fp, fileName, "w+");
	if (err != 0 || !fp) {
		perror("File opening failed");
		exit(1);
	}
	return fp;
}
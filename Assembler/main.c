#include <stdio.h>
#include "symbol.h"
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "codeGen.h"

///This file contains the main loop for the assembler///
///There are currently two forms of pseudo code for this main loop show below///

int main(int argc, char** argv) {
	const char* fileName = "input/Pong/Pong.asm";
	const char* outputFileName = "output/output.hack";
	int pass = 1;
	Instruction_t instruct;
	AR_t* advanceOuput = malloc(sizeof(AR_t));
	advanceOuput->command = malloc(sizeof(command_t));
	symbolTable_p symbTable = createSymbolTable();
	symbTable = addPredefSymbs(symbTable);
	FILE* fp = openFile(fileName);
	//int lineNumber = 0;
	command_t* currCommand = malloc(sizeof(command_t));
	int memAddress = 0;
	while (areThereMoreCommands(fp)) {
		advanceOuput = advancePass1(currCommand, fp);
		currCommand = advanceOuput->command;
		memAddress += advanceOuput->addresses;
		if (strcmp(currCommand->command, "//ENDOFFILE") == 0) {
			break;
		}
		instruct = parse(currCommand, pass, symbTable, memAddress);
		if (instruct.A != -2) {
			memAddress++;
		}
	}
	fclose(fp);
	FILE* Rewindfp = openFile(fileName);
	FILE* outputFp = openOutputFile(outputFileName);
	pass = 2;
	memAddress = 16;
	while (1) {
		currCommand = advancePass2(currCommand, Rewindfp);
		if (areThereMoreCommands(Rewindfp) == false) {
			break;
		}
		if (currCommand->type == N) {
			break;
		}
		instruct = parse(currCommand, pass, symbTable, memAddress);
		if (instruct.A < 0 && instruct.C.comp == nullcomp) {
			instruct.A *= -1;
			instruct.A -= 1;
			memAddress++;
		}
		GenerateCode(&instruct, outputFp);
	}
	fclose(outputFp);
	fclose(Rewindfp);
	//destroyCommand(currCommand);
}
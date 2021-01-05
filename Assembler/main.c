#include <stdio.h>
#include "symbol.h"
#include "assemble.h"

///This file contains the main loop for the assembler///
///There are currently two forms of pseudo code for this main loop show below///

int main(int argc, char** argv) {
	const char* fileName = "input/Pong/Pong.asm";
	const char* outputFileName = "output/output.hack";
	int pass = 1;
	symbolTable_p symbTable = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	symbTable = addPredefSymbs(symbTable, values);
	FILE* fp = openFile(fileName);
	int lineNumber = 0;
	command_t* currCommand = malloc(sizeof(command_t));
	while (areThereMoreCommands(fp)) {
		lineNumber++;
		currCommand = advancePass1(currCommand, fp);
		if (strcmp(currCommand->command, "//ENDOFFILE") == 0) {
			break;
		}
		parse(currCommand, pass, symbTable);
	}
	fclose(fp);
	FILE* Rewindfp = openFile(fileName);
	FILE* outputFp = openOutputFile(outputFileName);
	lineNumber = 0;
	pass = 2;
	while (areThereMoreCommands(Rewindfp)) {
		lineNumber++;
		currCommand = advancePass2(currCommand, Rewindfp);
		if (currCommand->type == N) {
			break;
		}
		Instruction_t instruct = parse(currCommand, pass, symbTable);
		GenerateCode(&instruct, outputFp);
	}
	fclose(outputFp);
	fclose(Rewindfp);
	//destroyCommand(currCommand);
}
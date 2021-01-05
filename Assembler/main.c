#include <stdio.h>
#include "symbol.h"
#include "assemble.h"

///This file contains the main loop for the assembler///
///There are currently two forms of pseudo code for this main loop show below///

int main(int argc, char** argv) {
	const char* fileName = "input/Pong/PongL.asm";
	const char* outputFileName = "output/output.hack";
	int pass = 1;
	symbolTable_p symbTable = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
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
	/*
		//First pass
		Parse command line
		create a symbol table
		add all predef symbols to the table
		open input file
		while(not end of file):
			read a line
			strip comments and whitespace
			parse the curr instruction
				- if currLine is L instruction parse the line
				- add the label to the symbol Table with value(curr program counter)
		Rewind input file

		//Second Pass
		open output file
		while(not end of file):
			read a line
			strip comments and whitespace
			parse the curr instruction
				- Determine A or C instruction
				- Parse the curr instruction based on type
			gen code based on parsed instruction
			write code to the output file

		close i/o files
		free symbol table and curr command memory
		*/
}
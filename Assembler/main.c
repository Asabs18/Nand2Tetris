#include <stdio.h>
#include "symbol.h"
#include "assemble.h"

///This file contains the main loop for the assembler///
///There are currently two forms of pseudo code for this main loop show below///

int main(int argc, char** argv) {
	/*
	//?????????????????????//
	//Read in the necessary items from the command line i.e the i/o files
	Parse Command Line
	//Creates the current command, this command is blank at the current point in time
	currCommand = createCommand(file);
	//createSymbolTable will create a new blank table and fill it in with the 23 predef values. 
	symbolTable_t table = createSymbolTable();
	//pass refers to the current pass of the command line. This var is more visual than functional
	int pass = 1;
	//this loop will call the function areThereMoreCommands that returns true if there are more commands and false otherwise
	while(areThereMoreCommands){
	//advance will find the next valid command in the file ignoring whitespace and comments and commands its not looking for(L commands) and will fill the currCommand with the new line and its attributes
		currCommand = advance(currCommand, pass);
		//parseLInstruction will take the current L instruction and check if its in the symbol table if so it is ignored, if not it is added with the next available memory address.
		parseLInstruction(table, currCommand);
	}
	pass = 2;
	//go back to the start of the file for the second pass
	resetFile
	//this loop is ran again to account for the second pass 
	while(areThereMoreCommands){
	//advance will now find the valid A and C commands and will ignore everything else in the file
		advance(currCommand, pass);
		//checks to see if the currCommand is A so it knows which parse function to call
		if(currCommand.type == A){
			parseAInctruction(table, currCommand);
		}
		//otherwise the command must be a C command because advance() outputs are binary
		else{
			parseCInstruction(currCommand);
		}
	}
	write to output file
	//frees all allocated memory that was created for this program
	free(currCommand, Symbol Table)
	//??????????????????????????//
	*/

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
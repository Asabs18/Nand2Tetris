#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "munit.h"
#include "tokenizer.h"
#include "symbol.h"
#include "_symbol.h"


#define MAXSIZE 100
#define EMPTYVAL 0
///this file contains all function declarations that have to do with parsing or handling the command/// 

AR_t* createAR_t() {
	//TODO: LEAKING MEMORY
	return calloc(1, sizeof(AR_t));
}

void destroyAR_t(AR_t* advanceOutput) {
	if (advanceOutput != NULL) {
		free(advanceOutput->command);
		free(advanceOutput);
		//memset(advanceOutput, 0, sizeof(AR_t));
	}
}

bool resetAR_t(AR_t* advanceOutput) {
	if (advanceOutput != NULL) {
		free(advanceOutput->command);
		memset(advanceOutput, 0, sizeof(AR_t));
		return true;
	}
	else {
		return false;
	}
}

FILE* openFile(const char* readFrom) {
	FILE* file;
	fopen_s(&file, readFrom, "r");
	assert(file != NULL);
	return file;
}

char* createCommand(FILE* file) {
	static char command[MAXSIZE];
	//gets the next command and sets it to command
	if (feof(file) == 0) {
		fgets(command, sizeof(command), file);
	}
	return command;
}

char* stripComments(char* command, size_t i) {
	//removes comments from the string
	static char newCommand[MAXSIZE];
	assert(i < MAXSIZE);
	//takes everything from a line except the comment 
	strncpy_s((char*)newCommand, sizeof(newCommand), command, i);
	//puts the new line character at the end of the string
	newCommand[i] = '\n';
	//removes any white space before the newline
	for (size_t j = i; j > 0; j--) {
		if (newCommand[j] == ' ') {
			newCommand[j] = '\n';
			i = j;
			break;
		}
	}
	//copies the new string over without white space
	assert(i < (MAXSIZE - 1));
	newCommand[i + 1] = '\0';
	return (char*)newCommand;
}

char* checkComments(char* command, size_t size) {
	//Checks if the currCommand is or has a comment
	for (size_t i = 0; i < size; i++) {
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
				char* temp = command;
				command = _strdup(stripComments(command, i));
				free(temp);
				return command; //break; //HACK: try and clean up returns and calls in checkComments
			}
		}
	}
	return _strdup(command);
}

char* stripWhiteSpace(char* command) {
	//creates buffer for new command
	char newCommand[MAXSIZE];
	int newCommandIndex = 0;
	//loops through the command and if it finds whitespace, don't copy it into the buffer
	for (size_t i = 0; i < strlen(command); i++) {
		if (command[i] != ' ' && command[i] != '\t' && command[i] != '\"') {
			newCommand[newCommandIndex] = command[i];
			newCommandIndex++;
		}
	}
	//ends the buffer
	newCommand[newCommandIndex] = '\0';
	command = _strdup(newCommand);
	return command;
}

//moves the current command to the next valid line
AR_t* advancePass1(command_t* currCommand, FILE* readFrom) {
	AR_t* output = createAR_t();
	output->addresses = 0;
	output->command = NULL;
	//runs until the return statement is hit in the loop
	output->command = updateCommand(currCommand, readFrom);
	while (true) {
		//if the current line is a comment get the next line
		assert(output != NULL);
		assert(output->command != NULL);
		//output->command = updateCommand(currCommand, readFrom);
		while (output->command->command == NULL || strcmp(output->command->command, "//skip") == 0 || strcmp(output->command->command, "\n") == 0) {
			output->command = updateCommand(currCommand, readFrom);
			if (areThereMoreCommands(readFrom) == false) {
				output->command->command = "//ENDOFFILE";
				break;
			}
		}
		//if the command is an L command return it
		if (output->command->type == L && output->command->type != N) {
			return output;
		}
		//Otherwise get the next line
		else if (areThereMoreCommands(readFrom) == true) {
			output->addresses++;
			output->command = updateCommand(currCommand, readFrom);
		}
		if (areThereMoreCommands(readFrom) == false) {
			output->command->type = N;
			return output;
		}
	}
}

//moves the current command to the next valid line
AR_t* advancePass2(command_t* currCommand, FILE* readFrom) {
	AR_t* output = createAR_t();
	//output->command = malloc(sizeof(command_t));
	//output->addresses = 0;
	//output->command = NULL;
	output->command = updateCommand(currCommand, readFrom);
	while (true) {
		//get the next line if the current line is a comment
		assert(output != NULL);
		assert(output->command != NULL);
		//output->command = updateCommand(currCommand, readFrom);
		while (output->command->command == NULL || strcmp(output->command->command, "//skip") == 0 || strcmp(output->command->command, "\n") == 0 || output->command->type == L) {
			output->command = updateCommand(currCommand, readFrom);
			if (areThereMoreCommands(readFrom) == false) {
				output->command->command = "//ENDOFFILE";
				break;
			}
		}
		//return everything that is not an L command
		if (output->command->type != L && output->command->type != N) {
			return output;
		}
		//If the command is an L command get the next line
		/*else if (areThereMoreCommands(readFrom) == true) {
			output->command = updateCommand(currCommand, readFrom);
		}*/
		if (areThereMoreCommands(readFrom) == false) {
			output->command->type = N;
			return output;
		}
	}
}


command_t* updateCommand(command_t* currCommand, FILE* readFrom) {
	//gets a new command from the read file
	currCommand->command = createCommand(readFrom);
	currCommand->command = stripWhiteSpace(currCommand->command);
	//gets the length of the command
	size_t cmdLen = strlen(currCommand->command);
	char* checkedComment = checkComments(currCommand->command, cmdLen);
	checkedComment = strcmp(checkedComment, "") == 0 ? NULL : checkedComment;
	char* temp = currCommand->command;
	currCommand->command = checkedComment != NULL ? _strdup(checkedComment) : NULL;
	free(temp);
	currCommand = commandType(currCommand);
	//returns the new command
	return currCommand;
}

//returns the command type of the current command, A, C or L command 
command_t* commandType(command_t* currCommand) {
	size_t size = 0;
	//gets the size of the command
	if (currCommand->command != NULL && strcmp(currCommand->command, "\n") != 0) {
		size = strlen(currCommand->command);
		int lastPlace = 1;
		//looks for the null character in a string and updates the last place accordingly. 
		if (currCommand->command[size - lastPlace] == '\n' && size > 1) {
			lastPlace++;
		}
		//Checks for L command
		if (currCommand->command[0] == '(' && currCommand->command[size - lastPlace] == ')') {
			currCommand->type = L;
		}
		//Checks for A command
		else if (currCommand->command[0] == '@') {
			currCommand->type = A;
		}
		//otherwise is C command
		else {
			currCommand->type = C;
		}
		return currCommand;
	}
	else {
		currCommand->type = N;
		currCommand->command = "//skip";
		return currCommand;
	}
}
//checks if there are more commands in the file
bool areThereMoreCommands(FILE* readFrom) {
	bool isFileEnd = false;
	//feof() returns 0 is there are NOT lines left in a file
	if (feof(readFrom) == 0) {
		isFileEnd = true;
	}
	return isFileEnd;
}

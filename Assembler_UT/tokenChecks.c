#include <assert.h>
#include "assemble.h"
#include "munit_ex.h"
#include "tokenizer.h"
#include "parser.h"
#include "codeGen.h"

///These are all the functions for the assemblerChecks.c test suite///
///These tests handle all functions that are dealing with commands///

//Makes sure createCommand returns a command
static MunitResult
createCommandReturnsFirstCommand(const MunitParameter params[], void* data) {
	//Arrange
	FILE* fp = openFile("test.txt");
	if (!fp) {
		perror("File opening failed");
		return MUNIT_ERROR;
	}

	//Act
	char* command = createCommand(fp);

	//Assert
	munit_assert(strcmp(command, "//Hello\n") == 0);
	fclose(fp);
	return MUNIT_OK;
}

//Makes sure createCommand returns the next command
static MunitResult
createCommandSavesReadSpot(const MunitParameter params[], void* data) {
	//Arrange
	FILE* fp = openFile("test.txt");
	if (!fp) {
		perror("File opening failed");
		return MUNIT_ERROR;
	}
	char* command = createCommand(fp);
	if (strcmp(command, "//Hello\n") != 0) {
		return MUNIT_ERROR;
	}

	//Act
	char* command2 = createCommand(fp);

	//Assert
	munit_assert(strcmp(command2, "command1\n") == 0);
	fclose(fp);
	return MUNIT_OK;
}

//checkComments removes inline comments
static MunitResult
inlineCommentsAreRemoved(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "hello//remove me";

	//Act
	command = checkComments(command, strlen(command));

	//Assert
	munit_assert(strcmp(command, "hello\n") == 0);
	return MUNIT_OK;
}

//checkComments removes full line comments
static MunitResult
fullLineCommentsAreRemoved(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "//remove me";

	//Act
	command = checkComments(command, strlen(command));

	//Assert
	//munit_assert(command == NULL || strcmp(command, "//skip") == 0);
	munit_assert(CHECK_SKIP_COMMAND(command));
	return MUNIT_OK;
}

//check comments creates the correct string
static MunitResult
checkCommentsRemovesInlineStrings(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "command\n";
	char* command2 = "command //removeme\n";

	//Act
	command = checkComments(command, strlen(command));
	command2 = checkComments(command2, strlen(command2));

	//Assert
	munit_assert(strcmp(command, command2) == 0);
	return MUNIT_OK;
}


//advance returns valid command
static MunitResult
advanceReturnsValidCommand(const MunitParameter params[], void* data) {
	//Arrange
	FILE* fp = openFile("test.txt");
	if (!fp) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	char* command = createCommand(fp);
	command_t currCommand = { A, command };

	//Act
	AR_t* answer = advancePass2(&currCommand, fp);

	//Assert
	munit_assert(strcmp(answer->command->command, "command1\n") == 0);
	fclose(fp);
	destroyCommand(answer->command);
	return MUNIT_OK;
}

//advance returns label pass one 
static MunitResult
advanceReturnsLabelPassOne(const MunitParameter params[], void* data) {
	//Arrange
	FILE* fp = openFile("test.txt");
	if (!fp) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	char* command = "Empty";
	command_t currCommand = { A, command };

	//Act
	AR_t* answer = advancePass1(&currCommand, fp);

	//Assert
	munit_assert(strcmp(answer->command->command, "(command2)\n") == 0);
	fclose(fp);
	destroyCommand(answer->command);
	return MUNIT_OK;
}

//advance returns not label pass two
static MunitResult
advanceReturnsNotLabelPassTwo(const MunitParameter params[], void* data) {
	//Arrange
	FILE* fp = openFile("test.txt");
	if (!fp) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	char* command = "Empty";
	command_t currCommand = { A, command };

	//Act
	AR_t* answer = advancePass2(&currCommand, fp);

	//Assert
	munit_assert(strcmp(answer->command->command, "command1\n") == 0);
	fclose(fp);
	destroyCommand(answer->command);
	return MUNIT_OK;
}

//advance finds second label when needed
static MunitResult
advanceFindsSecondLabel(const MunitParameter params[], void* data) {
	//Arrange
	FILE* fp = openFile("test.txt");
	if (!fp) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	char* command = "Empty";
	command_t currCommand = { A, command };

	//Act
	AR_t* answer = advancePass1(&currCommand, fp);
	destroyCommand(answer->command);
	AR_t* answer2 = advancePass1(&currCommand, fp);

	//Assert
	munit_assert(strcmp(answer2->command->command, "(command6)\n") == 0);
	fclose(fp);
	destroyCommand(answer2->command);
	return MUNIT_OK;
}

//Command Type correctly returns L command 
static MunitResult
commandTypeReturnsLCommand(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "(hello)";
	command_t currCommand = { A, command };

	//Act
	command_t* type = commandType(&currCommand);

	//Assert
	munit_assert(type->type == L);
	return MUNIT_OK;
}

//Command Type correctly returns A command 
static MunitResult
commandTypeReturnsACommand(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "@hello";
	command_t currCommand = { A, command };

	//Act
	command_t* type = commandType(&currCommand);

	//Assert
	munit_assert(type->type == A);
	return MUNIT_OK;
}



//Command Type correctly returns C command 
static MunitResult
commandTypeReturnsCCommand(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "hello";
	command_t currCommand = { A, command };

	//Act
	command_t* type = commandType(&currCommand);

	//Assert
	munit_assert(type->type == C);
	return MUNIT_OK;
}

//declares the test suite to run each test in this file
MunitTest tokenCheck_tests[] = {
	munit_ex_register_test(createCommandReturnsFirstCommand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(createCommandSavesReadSpot, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(inlineCommentsAreRemoved, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(checkCommentsRemovesInlineStrings, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(fullLineCommentsAreRemoved, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(advanceReturnsValidCommand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(advanceReturnsLabelPassOne, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(advanceReturnsNotLabelPassTwo, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(advanceFindsSecondLabel, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(commandTypeReturnsLCommand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(commandTypeReturnsACommand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(commandTypeReturnsCCommand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
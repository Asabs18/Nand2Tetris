#include "assemble.h"
#include <assert.h>

static MunitResult
AssemblerReturnsTrue(const MunitParameter params[], void* data) {
	//Arrange
	bool result;
	//Act
	result = assemble();
	
	//Assert
	munit_assert_true(result);
	return MUNIT_OK;
}

static MunitResult
advanceIncrementsCommandsLineNumber() {
	//Arrange
	command_t command = { A, 0, "@i" };

	//Act
	command_t result = advance(command);

	//Assert
	assert(result.lineNumber > 0);
	return MUNIT_OK;
}
static MunitResult
commandTypeReturnsCorrectCommand() {

	//Arrange
	command_t command = { C, 0, "@i" };

	//Act
	commandType(command);

	//assert
	assert(command.type == A);
}
static MunitResult
areThereMoreCommandsReturnsTrueWhenNeeded() {
	//Arrange
	command_t command = { C, 0, "@i" };

	//Act
	bool result = areThereMoreCommands(command);

	//Assert
	assert(result == false);
}


//declares the test suite to run each test in this file
MunitTest assembleCheck_MT[] = {
	munit_register_test(AssemblerReturnsTrue, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_register_test(advanceIncrementsCommandsLineNumber, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_register_test(commandTypeReturnsCorrectCommand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_register_test(areThereMoreCommandsReturnsTrueWhenNeeded, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
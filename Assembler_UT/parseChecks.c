#include "assemble.h"
#include "parseChecks.h"
#include "munit_ex.h"

static void*
compTest1_setup(const MunitParameter params[], void* user_data) {
	commandTests_t* command = malloc(sizeof(commandTests_t));
	command->type = C;
	command->lineNum = 10;
	command->command = "0;JMP";
	return command;
}

static void
compTest1_tear_down(void* fixture) {
	free(fixture);
}

static void*
compTest2_setup(const MunitParameter params[], void* user_data) {
	commandTests_t* command = malloc(sizeof(commandTests_t));
	command->type = C;
	command->lineNum = 11;
	command->command = "M = D; JGT";
	return command;
}

static void
compTest2_tear_down(void* fixture) {
	free(fixture);
}

static char* name_params[] = {
  "one", "two", "three", "four", NULL
};

static char* val_params[] = {
  "0;JMP", "M = D; JGT", "D=M-D", "AM=M-1", NULL
};

static MunitParameterEnum test_params[] = {
  { "name", name_params },
  { "val", val_params },
  { NULL, NULL },
};

static MunitResult
ReturnsCorrectComp(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;


	//Act
	cInstruct_t instruction = parseCInstruction(currCommand);

	//Assert
	munit_assert(instruction.comp == zero);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectDest(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;

	//Act
	cInstruct_t instruction = parseCInstruction(currCommand);

	//Assert
	munit_assert(instruction.dest == nulldest);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectJump(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;

	//Act
	cInstruct_t instruction = parseCInstruction(currCommand);

	//Assert
	munit_assert(instruction.jump == JMP);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectComp2(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = stripWhiteSpace(currCommand->command);

	//Act
	cInstruct_t instruction = parseCInstruction(currCommand);

	//Assert
	munit_assert(instruction.comp == Dcomp);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectDest2(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = stripWhiteSpace(currCommand->command);

	//Act
	cInstruct_t instruction = parseCInstruction(currCommand);

	//Assert
	munit_assert(instruction.dest == Mdest);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectJump2(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = stripWhiteSpace(currCommand->command);

	//Act
	cInstruct_t instruction = parseCInstruction(currCommand);

	//Assert
	munit_assert(instruction.jump == JGT);
	return MUNIT_OK;
}

static MunitResult
IdentifiesCCommandCorrectly(const MunitParameter params[], void* data) { //TODO: Fix cCommand
	//Arrange
	char* command = "M=D;JGT";
	command_t currCommand = { C, 10, command };
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table, values);
	int pass = 2;

	//Act
	Instruction_t instruction = parse(&currCommand, pass, table);

	//Assert
	munit_assert(instruction.C.comp != nullcomp && instruction.C.dest != nulldest && instruction.C.jump != nulljump);
	return MUNIT_OK;
}

static MunitResult
IdentifiesACommandCorrectly(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "@10";
	command_t currCommand = { A, 10, command };
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table, values);
	int pass = 2;

	//Act
	Instruction_t instruction = parse(&currCommand, pass, table);

	//Assert
	munit_assert(instruction.A != 0);
	return MUNIT_OK;
}

static MunitResult
IdentifiesLCommandCorrectly(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "(LABEL)";
	command_t currCommand = { L, 10, command };
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table, values);
	int pass = 2;

	//Act
	Instruction_t instruction = parse(&currCommand, pass, table);

	//Assert
	munit_assert(instruction.C.comp == nullcomp && instruction.A == 0);
	return MUNIT_OK;
}

static MunitResult
destReturnsCorrectVal(const MunitParameter params[], void* data) {
	//Arrange
	munit_assert(data != NULL);
	command_t* currCommand = (command_t*)data;
	currCommand->command = stripWhiteSpace(currCommand->command);
	int destEndIndex = 1;

	//Act
	cInstruct_t instruction = { nullcomp, nulldest, nulljump };
	instruction = dest(currCommand, instruction, destEndIndex);

	//Assert
	munit_assert(instruction.dest == Mdest);
	return MUNIT_OK;
}

static MunitResult
compReturnsCorrectVal(const MunitParameter params[], void* data) {
	//Arrange
	munit_assert(data != NULL);
	command_t* currCommand = (command_t*)data;
	currCommand->command = stripWhiteSpace(currCommand->command);

	//Act
	cInstruct_t instruction = { nullcomp, Mdest, JMP };
	instruction = comp(currCommand, instruction);

	//Assert
	munit_assert(instruction.comp == Dcomp);
	return MUNIT_OK;
}

static MunitResult
jumpReturnsCorrectVal(const MunitParameter params[], void* data) {
	//Arrange
	munit_assert(data != NULL);
	command_t* currCommand = (command_t*)data;
	currCommand->command = stripWhiteSpace(currCommand->command);
	int jumpStartIndex = 4;

	//Act
	cInstruct_t instruction = { nullcomp, nulldest, nulljump };
	instruction = jump(currCommand, instruction, jumpStartIndex);

	//Assert
	munit_assert(instruction.jump == JGT);
	return MUNIT_OK;
}

//declares the test suite to run each test in this file
MunitTest parseCheck_tests[] = {
	munit_ex_register_test(IdentifiesCCommandCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(IdentifiesACommandCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(IdentifiesLCommandCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(destReturnsCorrectVal, compTest2_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(compReturnsCorrectVal, compTest2_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(jumpReturnsCorrectVal, compTest2_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

//Tests specifically for the C-Instruction
MunitTest parseCheckForCInstruct_tests[] = { //TODO: change naming
	munit_ex_register_test(ReturnsCorrectComp, compTest1_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectDest, compTest1_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectJump, compTest1_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectComp2, compTest2_setup, compTest2_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectDest2, compTest2_setup, compTest2_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectJump2, compTest2_setup, compTest2_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
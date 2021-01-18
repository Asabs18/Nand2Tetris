#include "assemble.h"
#include "parseChecks.h"
#include "munit_ex.h"
#include "tokenizer.h"
#include "parser.h"
#include "codeGen.h"

static void*
compTest1_setup(const MunitParameter params[], void* user_data) {
	commandTests_t* command = malloc(sizeof(commandTests_t));
	command->type = C;
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
	currCommand->command = "0;JMP";
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);

	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.comp == zero);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectDest(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = "0;JMP";
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);

	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.dest == nulldest);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectJump(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = "0;JMP";
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.jump == JMP);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectComp2(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = "M = D; JGT";
	currCommand->command = stripWhiteSpace(currCommand->command);
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.comp == Dcomp);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectDest2(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = "M = D; JGT";
	currCommand->command = stripWhiteSpace(currCommand->command);
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.dest == Mdest);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectJump2(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = (command_t*)data;
	currCommand->command = "M = D; JGT";
	currCommand->command = stripWhiteSpace(currCommand->command);
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.jump == JGT);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectComp3(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = malloc(sizeof(command_t));
	currCommand->type = C;
	currCommand->command = "MD = -1; JMP";
	currCommand->command = stripWhiteSpace(currCommand->command);
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.comp == negOne);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectDest3(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = malloc(sizeof(command_t));
	currCommand->type = C;
	currCommand->command = "MD = -1; JMP";
	currCommand->command = stripWhiteSpace(currCommand->command);

	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.dest == MD);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
ReturnsCorrectJump3(const MunitParameter params[], void* data) {
	//Arrange
	command_t* currCommand = malloc(sizeof(command_t));
	currCommand->type = C;
	currCommand->command = "MD = -1; JMP";
	currCommand->command = stripWhiteSpace(currCommand->command);

	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//Act
	cInstruct_t instruction = parseCInstruction(currCommand, compTable, destTable, jumpTable);

	//Assert
	munit_assert(instruction.jump == JMP);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
IdentifiesCCommandCorrectly(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "M=D;JGT";
	command_t currCommand = { C, command };
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table);
	int pass = 2;
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);

	//Act
	Instruction_t instruction = parse(&currCommand, pass, table, 10, jumpTable, destTable, compTable);

	//Assert
	munit_assert(instruction.C.comp != nullcomp && instruction.C.dest != nulldest && instruction.C.jump != nulljump);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
IdentifiesACommandCorrectly(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "@10";
	command_t currCommand = { A, command };
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table);
	int pass = 2;
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);

	//Act
	Instruction_t instruction = parse(&currCommand, pass, table, 10, jumpTable, destTable, compTable);

	//Assert
	munit_assert(instruction.A != 0);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
IdentifiesLCommandCorrectly(const MunitParameter params[], void* data) {
	//Arrange
	char* command = "(LABEL)";
	command_t currCommand = { L, command };
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table);
	int pass = 1;
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);

	//Act
	Instruction_t instruction = parse(&currCommand, pass, table, 10, jumpTable, destTable, compTable);

	//Assert
	munit_assert(instruction.C.comp == nullcomp && instruction.A == -2);
	destroySymbolTable(compTable);
	destroySymbolTable(destTable);
	destroySymbolTable(jumpTable);
	return MUNIT_OK;
}

static MunitResult
destReturnsCorrectVal(const MunitParameter params[], void* data) {
	//Arrange
	munit_assert(data != NULL);
	command_t* currCommand = (command_t*)data;
	currCommand->command = "M = D; JGT";
	currCommand->command = stripWhiteSpace(currCommand->command);
	int destEndIndex = 1;
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);

	//Act
	cInstruct_t instruction = { nullcomp, nulldest, nulljump };
	instruction = dest(currCommand, instruction, destEndIndex, destTable);

	//Assert
	munit_assert(instruction.dest == Mdest);
	return MUNIT_OK;
}

static MunitResult
compReturnsCorrectVal(const MunitParameter params[], void* data) {
	//Arrange
	munit_assert(data != NULL);
	command_t* currCommand = (command_t*)data;
	currCommand->command = "M = D; JGT";
	int Ceq = 1;
	int Csc = 3;
	currCommand->command = stripWhiteSpace(currCommand->command);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);

	//Act
	cInstruct_t instruction = { nullcomp, Mdest, JMP };
	instruction = comp(currCommand, instruction, Ceq, Csc, compTable);

	//Assert
	munit_assert(instruction.comp == Dcomp);
	return MUNIT_OK;
}

static MunitResult
jumpReturnsCorrectVal(const MunitParameter params[], void* data) {
	//Arrange
	munit_assert(data != NULL);
	command_t* currCommand = (command_t*)data;
	currCommand->command = "M = D; JGT";
	currCommand->command = stripWhiteSpace(currCommand->command);
	int jumpStartIndex = 4;
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);

	//Act
	cInstruct_t instruction = { nullcomp, nulldest, nulljump };
	instruction = jump(currCommand, instruction, jumpStartIndex, jumpTable);

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
MunitTest parseCheckForCInstruct_tests[] = {
	munit_ex_register_test(ReturnsCorrectComp, compTest1_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectDest, compTest1_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectJump, compTest1_setup, compTest1_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectComp2, compTest2_setup, compTest2_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectDest2, compTest2_setup, compTest2_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectJump2, compTest2_setup, compTest2_tear_down, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectComp3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectDest3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(ReturnsCorrectJump3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
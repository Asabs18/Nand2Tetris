#include "assemble.h"
#include "munit_ex.h"
#include <assert.h>
#include "tokenizer.h"
#include "parser.h"
#include "codeGen.h"

static MunitResult
intToAsciiConversionValid1(const MunitParameter params[], void* data) {
	//Arrange
	int intVal = 10;
	char* output;

	//Act
	output = intToAscii(intVal);

	//Assert
	munit_assert(strcmp(output, "1010") == 0);
	return MUNIT_OK;
}

static MunitResult
intToAsciiConversionValid2(const MunitParameter params[], void* data) {
	//Arrange
	int intVal = 0xA80;
	char* output;

	//Act
	output = intToAscii(intVal);

	//Assert
	munit_assert(strcmp(output, "101010000000") == 0);
	return MUNIT_OK;
}

static MunitResult
GenerateCodeReturnsTrue1(const MunitParameter params[], void* data) {
	//Arrange
	cInstruct_t cInstruct = { nullcomp, nulldest, nulljump };
	Instruction_t instruct = { cInstruct, 12 };
	bool output;
	FILE* fp = openOutputFile("Output/output.hack");

	//Act
	output = GenerateCode(&instruct, fp);
	fclose(fp);

	//Assert
	munit_assert_true(output);
	return MUNIT_OK;
}

static MunitResult
GenerateCodeReturnsTrue2(const MunitParameter params[], void* data) {
	//Arrange
	cInstruct_t cInstruct = { Mcomp, nulldest, nulljump };
	Instruction_t instruct = { cInstruct, 0 };
	bool output;
	FILE* fp = openOutputFile("Output/output2.hack");

	//Act
	output = GenerateCode(&instruct, fp);
	fclose(fp);

	//Assert
	munit_assert_true(output);
	return MUNIT_OK;
}

static MunitResult
GenerateCodeReturnsTrue3(const MunitParameter params[], void* data) {
	//Arrange
	cInstruct_t cInstruct = { Mcomp, MD, JMP };
	Instruction_t instruct = { cInstruct, 0 };
	bool output;
	FILE* fp = openOutputFile("Output/output3.hack");

	//Act
	output = GenerateCode(&instruct, fp);
	fclose(fp);

	//Assert
	munit_assert_true(output);
	return MUNIT_OK;
}

static MunitResult
GenerateCodeReturnsTrue4(const MunitParameter params[], void* data) {
	//Arrange
	cInstruct_t cInstruct1 = { Mcomp, MD, JMP };
	Instruction_t instruct1 = { cInstruct1, 0 };

	cInstruct_t cInstruct2 = { nullcomp, nulldest, nulljump };
	Instruction_t instruct2 = { cInstruct1, 4 };
	bool output, output2;
	FILE* fp = openOutputFile("Output/output4.hack");

	//Act
	output = GenerateCode(&instruct1, fp);
	output2 = GenerateCode(&instruct2, fp);
	fclose(fp);

	//Assert
	munit_assert_true(output || output2);
	return MUNIT_OK;
}

static MunitResult
GenerateCodeReturnsTrue5(const MunitParameter params[], void* data) {
	//Arrange
	cInstruct_t cInstruct1 = { Dcomp, Mdest, JGT };
	Instruction_t instruct1 = { cInstruct1, 0 };

	cInstruct_t cInstruct2 = { nullcomp, nulldest, nulljump };
	Instruction_t instruct2 = { cInstruct2, 16 };

	cInstruct_t cInstruct3 = { Mcomp, MD, JMP };
	Instruction_t instruct3 = { cInstruct3, 0 };
	bool output, output2, output3;
	FILE* fp = openOutputFile("Output/output5.hack");

	//Act
	output = GenerateCode(&instruct1, fp);
	output2 = GenerateCode(&instruct2, fp);
	output3 = GenerateCode(&instruct3, fp);

	fclose(fp);

	//Assert
	munit_assert_true(output || output2 || output3);
	return MUNIT_OK;
}

static MunitResult
generateA_CommandReturnsTrue(const MunitParameter params[], void* data) {
	//Arrange
	bool output;
	FILE* fp = openOutputFile("Output/output3.hack");

	//Act
	output = generateA_Command(13, fp);
	fclose(fp);

	//Assert
	munit_assert_true(output);
	return MUNIT_OK;
}

static MunitResult
generateC_CommandReturnsTrue(const MunitParameter params[], void* data) {
	//Arrange
	cInstruct_t cInstruct = { Mcomp, MD, JMP };
	bool output;
	FILE* fp = openOutputFile("Output/output3.hack");

	//Act
	output = generateC_Command(cInstruct, fp);
	fclose(fp);

	//Assert
	munit_assert_true(output);
	return MUNIT_OK;
}


MunitTest codeGenCheck_tests[] = {
	munit_ex_register_test(intToAsciiConversionValid1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(intToAsciiConversionValid2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(GenerateCodeReturnsTrue1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(GenerateCodeReturnsTrue2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(GenerateCodeReturnsTrue3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(GenerateCodeReturnsTrue4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(GenerateCodeReturnsTrue5, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(generateA_CommandReturnsTrue, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(generateC_CommandReturnsTrue, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
#include "munit_ex.h"
#include "parseChecks.h"
#include "symbolChecks.h"
#include "tokenChecks.h"
#include "codeGenChecks.h"
#include "debug.h"

///main file for unit testing///
///This file creates 2 test suites to make different levels of abstraction///
///This will run all tests in assemblerChecks.c and symbolChecks.c///

const MunitSuite Parse_C_test_suite[] = {
	{ munit_ex_register_sub_suite(parseCheckForCInstruct, NULL) },
	{ NULL }
};

//The ACL test suite calls the assembleCheck Tests
const MunitSuite Assembler_test_suite[] = {
	{ munit_ex_register_sub_suite(symbolTable , NULL) },
	{ munit_ex_register_sub_suite(tokenCheck, NULL) },
	{ munit_ex_register_full_sub_suite_easy(parseCheck, parseCheck_tests, Parse_C_test_suite, 1) },
	{ munit_ex_register_sub_suite(codeGenCheck, NULL) },
	{ NULL }
};

//The root test suite calls the Assembler test suite
const MunitSuite root_test_suite = {
	munit_ex_register_empty_sub_suite(Assembler, Assembler_test_suite)
};

//main runs the root test suite
int main(int argc, char** argv) {
	initialize_debugging();
	//int* test = malloc(sizeof(int)); //FOR SOME REASON MEM LEAKS ONLY SHOW WHEN UNCOMMENTED
	int output = munit_suite_main(&root_test_suite, NULL, argc, argv);
	//terminate_debugging(); //TODO: Fix memory leaks
	return output;
}
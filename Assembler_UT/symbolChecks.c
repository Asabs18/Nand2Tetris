#include <assert.h>
#include "symbol.h"
#include "assemble.h"
#include "munit_ex.h"
#include "munit.h"
#include "_symbol.h"

///These are all the functions for the symbolChecks.c test suite///
///These tests handle all functions that are dealing with the symbol_t struct or the symbolTable///

//makes sure the symbolTable creation function returns true
static MunitResult
symbolTableReturnsTrue(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p result;
	//Act
	result = createSymbolTable();

	//Assert
	munit_assert_true(result);
	destroySymbolTable(result);
	return MUNIT_OK;
}

//makes sure the printTable function returns true
static MunitResult
printTableReturnsTrue(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table, values);

	//Act
	bool output = printHash(table, stderr, "SCREEN");
	bool output2 = printHash(table, stderr, "KBD");

	//Assert
	munit_assert_true(output);
	munit_assert_true(output2);
	destroySymbolTable(table);
	return MUNIT_OK;
}

static MunitResult
TableHasRigthValues(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table, values);
	const char* screen = "SCREEN";

	//Act
	symbol_p symb = getVal(table, screen);

	//Assert
	munit_assert_int(*((int*)symb->value), ==, 16384);
	destroySymbolTable(table);
	return MUNIT_OK;
}

static MunitResult
TableHasRigthValues2(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = createSymbolTable();
	int values[] = { 16384, 24576, 0, 1, 2, 3, 4 };
	table = addPredefSymbs(table, values);

	//Act
	symbol_p symb = getVal(table, "KBD");

	//Assert
	munit_assert_int(*((int*)symb->value), == , 24576);
	destroySymbolTable(table);
	return MUNIT_OK;
}

//If passed a valid symbol, isStringValidsymbol says its valid
static MunitResult
isStringValidSymbolTrueWhenValid(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "hello";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert(result == true);
	return MUNIT_OK;
}

//isStringValidsymbol gives err if there is a leading number in the string
static MunitResult
isStringValidSymbolFalseWhenNotValidNum(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "1Hello";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert(result == false);
	return MUNIT_OK;
}


//When an invalid character is in the string the function returns false
static MunitResult
isStringValidSymbolFalseWhenNotValidChar(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "He;llo:";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert_false(result);
	return MUNIT_OK;
}

//Makes sure isStringValidSymbol sees that the last char is invalid
static MunitResult
isStringValidSymbolChecksWholeString(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "Hello;";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert(result == false);
	return MUNIT_OK;
}

//isStringValidSymbol wont fail if these special characters are in the string
static MunitResult
isStringValidSymbolChecksSpecialChars(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "_.$:";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert(result == true);
	return MUNIT_OK;
}

//Checks if there is any whitespace in the string and fails if so
static MunitResult
isStringValidSymbolReturnsFalseIfWhitespace(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "He llo";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert_false(result);
	return MUNIT_OK;
}

//Returns false if there is whitespace at the end of the string too
static MunitResult
isStringValidSymbolReturnsFalseWhitespaceAtEnd(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "Hello ";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert_false(result);
	return MUNIT_OK;
}

//Checks if isStringValidSymbol returns true if there is a number in the middle of the string
static MunitResult
isStringValidSymbolReturnsTrueIfNumInMid(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "He1llo";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert(result == true);
	return MUNIT_OK;
}

//Returns false if there are invalid symbols
static MunitResult
isStringValidSymbolReturnsFalseIfInvalidSymbol(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "*&%^&";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert_false(result);
	return MUNIT_OK;
}


//Returns true if there are capital letters in the string
static MunitResult
isStringValidSymbolReturnsTrueIfCaps(const MunitParameter params[], void* data) {
	//Arrange
	const char* string = "HELLO";

	//Act
	bool result = isStringValidSymbol(string);

	//Assert
	munit_assert(result == true);
	return MUNIT_OK;
}


//returns true if there is a valid insert
static MunitResult
InsertReturnsTrueWhenValid(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = createSymbolTable();
	char* key = "hello";
	char* value = "hello";

	//Act
	bool result = insert(table, key, value);

	//Assert
	munit_assert_true(result);
	destroySymbolTable(table);
	return MUNIT_OK;
}

//returns false when there is a invalid insert
static MunitResult
InsertReturnsFalseWhenInvalid(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = NULL;
	char* key = "hello";
	char* value = "hello";

	//Act
	bool result = insert(table, key, value);

	//Assert
	munit_assert_false(result);
	return MUNIT_OK;
}

//Checks if insert adds the correct values to the table
static MunitResult
InsertAddsToTable(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = createSymbolTable();
	symbol_p symb = createSymbol("key");
	setValue(table, symb, "value");
	symb->key = "key";
	symb->value = "value";

	//Act
	insert(table, symb->key, symb->value);

	//Assert
	symbol_p outKey = getVal(table, symb->key);
	munit_assert(outKey->key == "key");
	destroySymbol(symb);
	destroySymbolTable(table);
	return MUNIT_OK;
}

static MunitResult
InsertKeytoSymb(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = createSymbolTable();
	char* key = "hello";
	char* value = "hello";

	//Act
	insert(table, key, value);

	//Assert
	munit_assert(table->table->key = key);
	destroySymbolTable(table);
	return MUNIT_OK;
}

static MunitResult
InsertValtoSymb(const MunitParameter params[], void* data) {
	//Arrange
	symbolTable_p table = createSymbolTable();
	char* key = "hello";
	char* value = "hello";

	//Act
	insert(table, key, value);

	//Assert
	munit_assert(table->table->value = value);
	destroySymbolTable(table);
	return MUNIT_OK;
}

//Checks that create symbol does not return NULL
static MunitResult
createSymbolTableNotEqualNull(const MunitParameter params[], void* data) {
	//Arrange
	//none

	//Act
	symbolTable_p table = createSymbolTable();

	//Assert
	munit_assert(table != NULL);
	destroySymbolTable(table);
	return MUNIT_OK;
}

//Checks that table->table does equal NULL
static MunitResult
createSymbolTableSubTableEqualsNull(const MunitParameter params[], void* data) {
	//Arrange
	//none

	//Act
	symbolTable_p table = createSymbolTable();

	//Assert
	munit_assert(table->table == NULL);
	destroySymbolTable(table);
	return MUNIT_OK;
}

//Checks that the symbol is not NULL in create symbol
static MunitResult
createSymbolSymbolNotNull(const MunitParameter params[], void* data) {
	//Arrange
	//none

	//Act
	symbol_p symb = createSymbol("hello");

	//Assert
	munit_assert(symb != NULL);
	destroySymbol(symb);
	return MUNIT_OK;
}


//declares the test suite to run each test in this file
MunitTest symbolTable_tests[] = {
	munit_ex_register_test(symbolTableReturnsTrue, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(printTableReturnsTrue, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolTrueWhenValid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolFalseWhenNotValidNum, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolFalseWhenNotValidChar, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolChecksWholeString, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolChecksSpecialChars, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolReturnsFalseIfWhitespace, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolReturnsFalseWhitespaceAtEnd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolReturnsTrueIfNumInMid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolReturnsFalseIfInvalidSymbol, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(isStringValidSymbolReturnsTrueIfCaps, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(InsertReturnsTrueWhenValid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(InsertReturnsFalseWhenInvalid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(InsertAddsToTable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(InsertKeytoSymb, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(InsertValtoSymb, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(createSymbolTableNotEqualNull, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(createSymbolTableSubTableEqualsNull, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(createSymbolSymbolNotNull, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(TableHasRigthValues, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_ex_register_test(TableHasRigthValues2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
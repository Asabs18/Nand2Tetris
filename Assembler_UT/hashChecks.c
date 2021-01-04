#include "hash.h"
#include "assemble.h"
#include <assert.h>

static MunitResult
symbolTableReturnsTrue(const MunitParameter params[], void* data) {
	//Arrange
	bool result;
	//Act
	result = symbolTable();

	//Assert
	munit_assert_true(result);
	return MUNIT_OK;
}

static MunitResult
tableSizeIncreasesAfterInsert() {
	//Arrange
	table_t* table = symbolTable(/*0*/);
	int value = 5;
	const char* name = "test";
	//Act
	insert(*table, value, name);
	//Assert
	assert(table->size > 0);
	return MUNIT_OK;
}

static MunitResult
hashCodeReturnsCorrectNumType() {
	//Arrange
	table_t table = { 0,NULL };
	int key = -10;
	
	//Act ???
	int output = hashCode(&table, key);

	//Assert
	assert(output < 0);
	return MUNIT_OK;
}

static MunitResult
printTableReturnsTrue() {
	//Arrange
	table_t table = { 0,NULL };

	//Act
	bool output = printList(table);

	//Assert
	munit_assert_true(output);
	return MUNIT_OK;
}

static MunitResult
getValReturnsAVal() {
	//Arrange
	table_t table = { 0,NULL };
	char* key = "name";

	//Act
	symbol_t val = getVal(table, key);

	//Assert
	assert(val.key != "/0" && val.value != 0);
	return MUNIT_OK;
}

//declares the test suite to run each test in this file
MunitTest hashCheck_MT[] = {
	munit_register_test(symbolTableReturnsTrue, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_register_test(tableSizeIncreasesAfterInsert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_register_test(hashCodeReturnsCorrectNumType, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_register_test(printTableReturnsTrue, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	munit_register_test(getValReturnsAVal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
#include <cstdint>
#include <sstream>
#include "../../include/parser.hpp"
#include "../../include/token.hpp"
#include "../include/token.hpp"

static MunitResult
tokenizeReturnsValidToken1(const MunitParameter params[], void* data) {
    //Arrange
	std::stringstream file("push pop sub add function fn sub 10 15");
	parser_t* parser(file);
	 
	//Act
	token_t* token = parser->_tokenizer->tokenize();

	//Assert
	munit_assert_true(token->is_token());
    return MUNIT_SKIP;
}

static MunitResult
tokenizeReturnsValidToken2(const MunitParameter params[], void* data) {
    //Arrange
	std::stringstream file("sub add function fn sub 10 15");
	parser_t* parser(file);
	 
	//Act
	token_t* token = parser->_tokenizer->tokenize();

	//Assert
	munit_assert_true(token->is_token());
    return MUNIT_SKIP;
}

static MunitResult
tokenizeReturnsValidToken3(const MunitParameter params[], void* data) {
    //Arrange
	std::stringstream file("function fn sub 10 15");
	parser_t* parser(file);
	 
	//Act
	token_t* token = parser->_tokenizer->tokenize();

	//Assert
	munit_assert_true(token->is_token());
    return MUNIT_SKIP;
}

static MunitResult
tokenizeReturnsValidToken3(const MunitParameter params[], void* data) {
    //Arrange
	std::stringstream file("function fn sub 10 15");
	parser_t* parser(file);
	 
	//Act
	token_t* token = parser->_tokenizer->tokenize();

	//Assert
	munit_assert_true(token->is_token());
    return MUNIT_SKIP;
}

static MunitResult
tokenizeReturnsValidNumber1(const MunitParameter params[], void* data) {
    //Arrange
	std::stringstream file("10 15");
	parser_t* parser(file);
	 
	//Act
	token_t* token = parser->_tokenizer->tokenize();

	//Assert
	munit_assert_true(token->is_number());
    return MUNIT_SKIP;
}

static MunitResult
tokenizeReturnsValidNumber2(const MunitParameter params[], void* data) {
    //Arrange
	std::stringstream file("15");
	parser_t* parser(file);
	 
	//Act
	token_t* token = parser->_tokenizer->tokenize();

	//Assert
	munit_assert_true(token->is_number());
    return MUNIT_SKIP;
}

//declares the test suite to run each test in this file
MunitTest token_t_tests[] = {
    munit_ex_register_test(tokenizeReturnsValidToken1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    munit_ex_register_test(tokenizeReturnsValidToken2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    munit_ex_register_test(tokenizeReturnsValidToken3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    munit_ex_register_test(tokenizeReturnsValidNumber1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    munit_ex_register_test(tokenizeReturnsValidNumber2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

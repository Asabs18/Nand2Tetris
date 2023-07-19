// SUT
#include "../../include/parser.hpp"
// Test
#include "../include/parser.hpp"

// [dynamic_cast conversion - cppreference.com](https://en.cppreference.com/w/cpp/language/dynamic_cast)

// static MunitResult
// parseIdentifiesMaCommandsCorrectly(const MunitParameter params[], void* data) {
//     // Arrange
//     parser_t* parser = new parser_t(" pop local 1 ");
//     // Act
//     // try {
//     ma_instruction_t* instruction = dynamic_cast<ma_instruction_t*>(parser->parse());
//     delete parser;
//     // } catch (std::bad_cast) { };
//     // Assert
//     munit_assert_true(instruction->instruction == "pop" && instruction->memory_segment.memory_segment == "local" && instruction->index.value == 1);
//     return MUNIT_OK;
// }

// static MunitResult
// parseIdentifiesAlCommandsCorrectly(const MunitParameter params[], void* data) {
//     // Arrange
//     parser_t* parser = new parser_t(" add ");
//     // Act
//     al_instruction_t* instruction = dynamic_cast<al_instruction_t*>(parser->parse());
//     // Assert
//     munit_assert_true(instruction->instruction == "add");
//     return MUNIT_OK;
// }

// static MunitResult
// parseIdentifiesBrCommandsCorrectly(const MunitParameter params[], void* data) {
//     // Arrange
//     parser_t* parser = new parser_t(" goto LOOP ");
//     // Act
//     br_instruction_t* instruction = dynamic_cast<br_instruction_t*>(parser->parse());
//     // Assert
//     munit_assert_true(instruction->instruction == "goto" && instruction->label == "LOOP");
//     return MUNIT_OK;
// }

// static MunitResult
// parseIdentifiesFnCommandsCorrectly(const MunitParameter params[], void* data) {
//     // Arrange
//     parser_t* parser = new parser_t(" function func var1 var2 ");
//     // Act
//     fn_instruction_t* instruction = dynamic_cast<fn_instruction_t*>(parser->parse());
//     // Assert
//     munit_assert_true(instruction->instruction == "function" && instruction->name == "func" && instruction->number.value == 2);
//     return MUNIT_OK;
// }

//declares the test suite to run each test in this file
MunitTest parser_t_tests[] = {
    //munit_ex_register_test(parseIdentifiesMaCommandsCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    //munit_ex_register_test(parseIdentifiesAlCommandsCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    //munit_ex_register_test(parseIdentifiesBrCommandsCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    //munit_ex_register_test(parseIdentifiesFnCommandsCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
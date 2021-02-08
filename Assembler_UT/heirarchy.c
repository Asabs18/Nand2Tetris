#include "munit.h"

// /Assembler/symbolTable/isStringValidSymbol/1
// /Assembler/symbolTable/2
// /Assembler/symbolTable/3
// /Assembler/Tokenizer/checkComments/1
// /Assembler/Tokenizer/advance/2
// /Assembler/Tokenizer/3
// /Assembler/Tokenizer/4
// /Assembler/Tokenizer/5
// /Assembler/parser/parseCInstruction/1
// /Assembler/parser/parseAInstruction/2
// /Assembler/parser/parseLInstruction/3
// /Assembler/parser/4
// /Assembler/parser/5
// /Assembler/code_gen/1
// /Assembler/code_gen/2
// /Assembler/code_gen/3


// Name // Test Function // Setup Function // Tear-down Function // Options // Parameters
#define munit_ex_register_test(name, setup, tear_down, options, params) \
    { "/"#name, name, setup, tear_down, options, params }

// - test names: _name__tests()
// Name // Test Function // Setup Function // Tear-down Function // Options // Parameters
#define munit_ex_register_suite(name, tests, sub_suites, iterations, options) \
     "/"#name, (MunitTest*) tests, (MunitSuite*) sub_suites, iterations, options
#define munit_ex_register_full_sub_suite(name, tests, sub_suites, iterations, options) \
     munit_ex_register_suite(name, tests, sub_suites, iterations, options)
#define munit_ex_register_empty_sub_suite(name, sub_suites) \
    munit_ex_register_full_sub_suite(name, NULL, sub_suites, 1, MUNIT_SUITE_OPTION_NONE)
#define munit_ex_register_sub_suite(name, sub_suites) \
    munit_ex_register_full_sub_suite(name, name##_tests, sub_suites, 1, MUNIT_SUITE_OPTION_NONE)


// /n2t/hash/1
// /n2t/hash/2
// /n2t/hash/3
// /parser/symbol/1
// /parser/symbol/2
// /parser/symbol/3
// /parser/code_gen/a_instr/1
// /parser/code_gen/a_instr/2
// /parser/code_gen/a_instr/3
// /parser/code_gen/c_instr/1
// /parser/code_gen/c_instr/2
// /parser/code_gen/c_instr/3
// /parser/code_gen/l_instr/1
// /parser/code_gen/l_instr/2
// /parser/code_gen/l_instr/3

//static const MunitSuite n2t_sub_suites[] = {
//    { munit_ex_register_sub_suite(hash, NULL) },
//    { NULL }
//};
//static const MunitSuite code_gen_sub_suites[] = {
//    { munit_ex_register_sub_suite(a_instruction, NULL) },
//    { munit_ex_register_sub_suite(c_instruction, NULL) },
//    { munit_ex_register_sub_suite(l_instruction, NULL) },
//    { NULL }
//};
//static const MunitSuite parser_sub_suites[] = {
//    { munit_ex_register_sub_suite(symbol, NULL) },
//    { munit_ex_register_empty_sub_suite(code_gen, code_gen_sub_suites) },
//    { NULL }
//};
//static const MunitSuite hack_ass_sub_suites[] = {
//    { munit_ex_register_empty_sub_suite(n2t, n2t_sub_suites) },
//    { munit_ex_register_empty_sub_suite(parser, parser_sub_suites) },
//    { NULL }
//};
//static const MunitSuite hack_ass_suite = {
//    munit_ex_register_empty_sub_suite(, hack_ass_sub_suites)
//};
//int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
//    //nuance_sub_suites[0] = array_suite;
//    //assembler_sub_suites[0] = parser_suite;
//    //assembler_sub_suites[1] = code_gen_suite;
//    //root_sub_suites[0] = ph_suite;
//    //root_sub_suites[1] = assembler_suite;
//    return CRT_DUMP_MEMORY_LEAKS(), munit_suite_main(&hack_ass_suite, (void*)"Hack - Assembler", argc, argv);
//}
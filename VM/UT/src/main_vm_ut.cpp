#include "../include/parser.hpp"
#include "../include/token.hpp"

MunitTest dummy_tests[] = {
    // munit_ex_register_test(IdentifiesCCommandCorrectly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL),
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
const MunitSuite dummy_test_suite[] = {
    { munit_ex_register_sub_suite(dummy, NULL) },
    { NULL }
};


//The ACL test suite calls the assembleCheck Tests
const MunitSuite VM_test_suite[] = {
    { munit_ex_register_sub_suite(token_t , NULL) },
    { munit_ex_register_sub_suite(parser_t , NULL) },
    { munit_ex_register_sub_suite(dummy, NULL) },
    { munit_ex_register_full_sub_suite_easy(dummy, dummy_tests, dummy_test_suite, 1) },
    // { munit_ex_register_sub_suite(codeGenCheck, NULL) },
    { NULL }
};
//The root test suite calls the VM test suite
const MunitSuite root_test_suite = {
    munit_ex_register_empty_sub_suite(VM, VM_test_suite)
};
// TODO: Remove parser_t code - TESTING ONLY.
#include <string>
#include "../../include/parser.hpp"
//main runs the root test suite
int main_vm_ut(int argc, char* argv[]) {
    parser_t parser(std::string("djg"));
    return munit_suite_main(&root_test_suite, NULL, argc, argv);
}
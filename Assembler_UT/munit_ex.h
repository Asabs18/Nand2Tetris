#pragma once
#include "munit.h"


// Name // Test Function // Setup Function // Tear-down Function // Options // Parameters
#define munit_ex_register_test(name, setup, tear_down, options, params) \
    { "/"#name, name, setup, tear_down, options, params }

// TODO: w/examples, etc. Conventions:
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
//Easy versions of regFullSubSuite, auto fills in MUNIT_SUITE_OPTION_NONE
#define munit_ex_register_full_sub_suite_easy(name, tests, sub_suites, iterations) \
    munit_ex_register_full_sub_suite(name, tests, sub_suites, iterations, MUNIT_SUITE_OPTION_NONE)
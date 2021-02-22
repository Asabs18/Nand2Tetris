#pragma once
#include "assemble.h"
#include "munit.h"

typedef struct commandTests {
	commandType_t type;
	char* command;
}commandTests_t;

extern MunitTest parseCheck_tests[];
extern MunitTest parseCheckForCInstruct_tests[];
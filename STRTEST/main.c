#include "debug.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
	initialize_debugging();
	char source[] = "This is a test";

	_CrtMemState m1;
	_CrtMemState m2;
	_CrtMemState m3;
	_CrtMemCheckpoint(&m1);
	char* target = _strdup(source);
	free(target);
	_CrtMemCheckpoint(&m2);
	_CrtMemDifference(&m3, &m1, &m2);
	_CrtMemDumpStatistics(&m3);
	terminate_debugging();
}
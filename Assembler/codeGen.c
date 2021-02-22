#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "munit.h"
#include "codeGen.h"
#include "symbol.h"
#include "_symbol.h"

//defined values for below
#define MAXSIZE 100
#define EMPTYVAL 0


//CODE--GEN//
bool GenerateCode(Instruction_t* instruct, FILE* fp) {
	if (instruct->A != -1) {
		generateA_Command(instruct->A, fp);
	}
	else if (instruct->C.comp != nullcomp) {
		generateC_Command(instruct->C, fp);
	}
	else {
		return false;
	}
	return true;
}

bool produceOutput(uint16_t binVal, FILE* fp) {
	char* output = intToAscii(binVal);
	char* fileName = "output.hack";
	if (strlen(output) < 16) {
		for (size_t i = 0; i < (16 - strlen(output)); i++) {
			fprintf(fp, "0");
		}
	}
	fprintf(fp, "%s\n", output);
	return true;
}

bool generateC_Command(cInstruct_t command, FILE* fp) {
	uint16_t startVal = 0xE000;
	uint16_t output = startVal | (uint16_t)command.comp;
	output |= (uint16_t)command.dest;
	output |= (uint16_t)command.jump;
	return produceOutput(output, fp);
}

#define SIXTEEN_CHAR_OFF 0x7FFF
bool generateA_Command(int command, FILE* fp) {
	uint16_t output = (uint16_t)command & SIXTEEN_CHAR_OFF;
	return produceOutput(output, fp);;
}

char* intToAscii(int intIn) {
	static char buffer[MAXSIZE];
	_itoa_s(intIn, buffer, MAXSIZE, 2);
	return buffer;
}

FILE* openOutputFile(char* fileName) {
	FILE* fp;
	errno_t err = fopen_s(&fp, fileName, "w+");
	if (err != 0 || !fp) {
		perror("File opening failed");
		exit(1);
	}
	return fp;
}
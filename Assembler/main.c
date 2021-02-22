#include <stdio.h>
#include "symbol.h"
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "codeGen.h"
#include "debug.h"


#define OUTSIZE 20
int main(int argc, char** argv) {
	//create look-up tables for symbol values
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
			Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
			negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	symbolTable_p compTable = createSymbolTable();
	compTable = fillCompTable(compTable, compVals);
	static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	symbolTable_p destTable = createSymbolTable();
	destTable = fillDestTable(destTable, destVals);
	//open the read and write files using the correct names based on the file
	char output[OUTSIZE];
	const char* fileName = argv[1];
	const char* outputFileName = outName(argv[1], output);
	int pass = 1;
	//create the currCommand variables and create and init the symbol table
	Instruction_t instruct;
	AR_t* advanceOutput = malloc(sizeof(AR_t));
	advanceOutput->command = malloc(sizeof(command_t));
	symbolTable_p symbTable = createSymbolTable();
	symbTable = addPredefSymbs(symbTable);
	FILE* fp = openFile(fileName);
	command_t* currCommand = malloc(sizeof(command_t));
	int memAddress = 0;
	//PASS 1: go through the whole file and store all L commands in symbol table
	while (areThereMoreCommands(fp)) {
		advanceOutput = advancePass1(currCommand, fp);
		currCommand = advanceOutput->command;
		memAddress += advanceOutput->addresses;
		if (strcmp(currCommand->command, "//ENDOFFILE") == 0) {
			break;
		}
		instruct = parse(currCommand, pass, symbTable, memAddress, jumpTable, compTable, destTable);
		if (instruct.A != -2) {
			memAddress++;
		}
	}
	//reset the needed variables after pass 1
	fclose(fp);
	FILE* Rewindfp = openFile(fileName);
	FILE* outputFp = openOutputFile((char*)outputFileName);
	pass = 2;
	memAddress = 16;
	//PASS 2: go through all the files and update the symbol table or generate code based on the A and C(not L) commands
	while (1) {
		advanceOutput = advancePass2(currCommand, Rewindfp);
		currCommand = advanceOutput->command;
		if (areThereMoreCommands(Rewindfp) == false) {
			break;
		}
		if (currCommand->type == N) {
			break;
		}
		instruct = parse(currCommand, pass, symbTable, memAddress, jumpTable, destTable, compTable);
		if (instruct.A < 0 && instruct.C.comp == nullcomp) {
			instruct.A *= -1;
			instruct.A -= 1;
			memAddress++;
		}
		GenerateCode(&instruct, outputFp);
	}
	//free all tables and close both files
	fclose(outputFp);
	fclose(Rewindfp);
	destroySymbolTable(compTable);
	destroySymbolTable(jumpTable);
	destroySymbolTable(destTable);
	destroySymbolTable(symbTable);
	//NOTE: This program does contain multiple memory leaks VERSION WITH LESS LEAKS ON GITHUB
}
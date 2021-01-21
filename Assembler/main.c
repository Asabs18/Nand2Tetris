#include <stdio.h>
#include "symbol.h"
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "codeGen.h"
#include "debug.h"


#define OUTSIZE 20
int main(int argc, char** argv) {
	initialize_debugging();
	_CrtMemState m1;
	_CrtMemState m2;
	_CrtMemState m3;

	_CrtMemCheckpoint(&m1);
	jump_t jumpVals[] = { nulljump, JGT, JEQ, JGE, JLT, JNE, JLE, JMP };
	symbolTable_p jumpTable = createSymbolTable();
	_CrtMemCheckpoint(&m2);
	_CrtMemDifference(&m3, &m1, &m2);
	_CrtMemDumpStatistics(&m3);

	_CrtMemCheckpoint(&m1);
	jumpTable = fillJumpTable(jumpTable, jumpVals);
	_CrtMemCheckpoint(&m2);
	_CrtMemDifference(&m3, &m1, &m2);
	_CrtMemDumpStatistics(&m3);

	//static comp_t compVals[] = { zero, one, negOne, Dcomp, Acomp, notD, notA, negD, negA, Dplus,
	//		Aplus, Dminus, Aminus, DplusA, DminusA, AminusD, DandA, DorA, Mcomp, notM,
	//		negM, Mplus, Mminus, DplusM, DminusM, MminusD, DandM, DorM, nullcomp };
	//symbolTable_p compTable = createSymbolTable();
	//compTable = fillCompTable(compTable, compVals);
	//static dest_t destVals[] = { nulldest, Mdest, Ddest, MD, Adest, AM, AD, AMD };
	//symbolTable_p destTable = createSymbolTable();
	//destTable = fillDestTable(destTable, destVals);
	//char output[OUTSIZE];
	//const char* fileName = argv[1];
	//const char* outputFileName = outName(argv[1], output);
	//int pass = 1;
	//Instruction_t instruct;
	//AR_t* advanceOutput = (AR_t*)malloc(sizeof(AR_t));
	////advanceOutput->command = (AR_t*)malloc(sizeof(command_t));
	//advanceOutput->command = (command_t*)malloc(sizeof(command_t));
	//symbolTable_p symbTable = createSymbolTable();
	//symbTable = addPredefSymbs(symbTable);
	//FILE* fp = openFile(fileName);
	//command_t* currCommand = (command_t*)malloc(sizeof(command_t));
	//int memAddress = 0;
	//while (areThereMoreCommands(fp)) {
	//	advanceOutput = advancePass1(currCommand, fp);
	//	currCommand = advanceOutput->command;
	//	memAddress += advanceOutput->addresses;
	//	if (strcmp(currCommand->command, "//ENDOFFILE") == 0) {
	//		break;
	//	}
	//	instruct = parse(currCommand, pass, symbTable, memAddress, jumpTable, compTable, destTable);
	//	if (instruct.A != -2) {
	//		memAddress++;
	//	}
	//}
	//rewind(fp);
	////fclose(fp);
	////FILE* Rewindfp = openFile(fileName);
	//FILE* outputFp = openOutputFile((char*)outputFileName);
	//// TODO: Replace w/mnemonics
	//pass = 2;
	//memAddress = 16;
	////while (1) {
	//while (true) {
	//	//advanceOutput = advancePass2(currCommand, Rewindfp);
	//	advanceOutput = advancePass2(currCommand, fp);
	//	currCommand = advanceOutput->command;
	//	//if (areThereMoreCommands(Rewindfp) == false) {
	//	if (areThereMoreCommands(fp) == false) {
	//		break;
	//	}
	//	if (currCommand->type == N) {
	//		break;
	//	}
	//	instruct = parse(currCommand, pass, symbTable, memAddress, jumpTable, destTable, compTable);
	//	if (instruct.A < 0 && instruct.C.comp == nullcomp) {
	//		instruct.A *= -1;
	//		instruct.A -= 1;
	//		memAddress++;
	//	}
	//	GenerateCode(&instruct, outputFp);
	//}
	//fclose(outputFp);
	////fclose(Rewindfp);
	//destroySymbolTable(compTable);
	destroySymbolTable(jumpTable);
	//destroySymbolTable(destTable);
	//destroySymbolTable(symbTable);
	//destroyCommand(currCommand);
	////destroyCommand(advanceOutput);
	//// BUG
	////destroyCommand(advanceOutput->command);
	////free(advanceOutput);
	terminate_debugging();
}
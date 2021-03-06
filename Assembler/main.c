#include <stdio.h>
#include "symbol.h"
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "codeGen.h"
#include "debug.h"
#include <assert.h>


#define OUTSIZE 20
int main(int argc, char** argv) {
	initialize_debugging();
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
	char output[OUTSIZE];
	const char* fileName = argv[1];
	const char* outputFileName = outName(argv[1], output);
	int pass = 1;
	Instruction_t instruct;
	AR_t* advanceOutput = NULL;
	symbolTable_p symbTable = createSymbolTable();
	symbTable = addPredefSymbs(symbTable);
	FILE* fp = openFile(fileName);
	command_t* currCommand = (command_t*)malloc(sizeof(command_t));
	int memAddress = 0;
	while (areThereMoreCommands(fp)) {
		resetAR_t(advanceOutput);
		advanceOutput = advancePass1(currCommand, fp);
		assert(advanceOutput != NULL);
		assert(advanceOutput->command != NULL);
		currCommand->command = _strdup(advanceOutput->command->command);
		memAddress += advanceOutput->addresses;
		if (strcmp(currCommand->command, "//ENDOFFILE") == 0) {
			free(currCommand->command);
			break;
		}
		instruct = parse(currCommand, pass, symbTable, memAddress, jumpTable, compTable, destTable);
		if (instruct.A != -2) {
			memAddress++;
		}
		free(currCommand->command);
	}
	currCommand->command = NULL;
	currCommand->type = N;
	rewind(fp);
	FILE* outputFp = openOutputFile((char*)outputFileName);
	pass = 2;
	memAddress = 16;
	//TODO: add debugging func for pass 1 and return report
	//resetAR_t(advanceOutput);
	//destroyAR_t(advanceOutput);
	while (true) {
		resetAR_t(advanceOutput);
		advanceOutput = advancePass2(currCommand, fp);
		//TODO: LEAKING MEMORY
		currCommand->command = _strdup(advanceOutput->command->command);
		if (areThereMoreCommands(fp) == false) {
			free(currCommand->command);
			break;
		}
		if (currCommand->type == N) { //HACK: add to if on line 66
			free(currCommand->command);
			break;
		}
		instruct = parse(currCommand, pass, symbTable, memAddress, jumpTable, destTable, compTable);
		if (instruct.A < 0 && instruct.C.comp == nullcomp) {
			instruct.A *= -1;
			instruct.A -= 1;
			memAddress++;
		}
		GenerateCode(&instruct, outputFp);
		free(currCommand->command);//HACK: move free out of loop
	}
	fclose(outputFp);
	fclose(fp);
	destroySymbolTable(compTable);
	destroySymbolTable(jumpTable);
	destroySymbolTable(destTable);
	destroySymbolTable(symbTable);
	//destroyCommand(currCommand);
	//free(currCommand);
	destroyAR_t(advanceOutput);
	terminate_debugging();
}
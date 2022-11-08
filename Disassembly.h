//
// Created by Anthony Norderhaug on 11/6/22.
//

#ifndef INC_530PROGRAM2_DISASSEMBLY_H
#define INC_530PROGRAM2_DISASSEMBLY_H

#include "Instruction.h"
#include "Formatting.h"
#include "Table.h"

string deriveTA(Instruction instr, string base);

string buildHeader(string record, string &progName, ofstream& outputFile);
void buildBase(string symbol, ofstream& outputFile);
void buildEnd(string name, ofstream& outputFile);

void buildSymbol(int &addr, string symbol, int distance, ofstream& outputFile);
void buildLiteral(int &addr, literal val, ofstream& outputFile);

void buildInstruction(Instruction instr, int& curAddr, Table symLit, string& baseHex, ofstream& outputFile);


#endif //INC_530PROGRAM2_DISASSEMBLY_H

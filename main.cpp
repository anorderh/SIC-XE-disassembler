/**
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * main.cpp => file handling & processing SIC/XE instructions
 */

#include <iostream>
#include <list>

#include "Instruction.h"
#include "Formatting.h"
#include "Table.h"
#include "Disassembly.h"

/**
 * accountSymbols() reserves space for SYMBOLS between the current address
 * and a target address.
 *
 * @param addr
 * @param hexTarget         ADDR of next record's start or program end
 * @param remaining         symbols not addressed yet
 * @param symLit
 * @param outputFile
 */
void accountSymbols(int &addr, string hexTarget, list<int> &remaining,
                    Table symLit, ofstream& outputFile) {
    int target = hexToDecimal(hexTarget);

    while (addr < target) {
        // use addr to get next symbol, pop
        string addrKey = formatHex(decimalToHex(remaining.front()), 6);
        remaining.pop_front();


        if (remaining.empty() || remaining.front() > target) {
            // if last symbol, use target to find dispositon
            buildSymbol(addr, symLit.symbolMap[addrKey], target-addr, outputFile);
            break;
        } else {
            buildSymbol(addr, symLit.symbolMap[addrKey], remaining.front() - addr, outputFile);
        }
    }
}

/**
 * process() parses the machine code for instructions, referencing SYMTAB and LITTAB
 *
 * @param file
 * @param symLitTable
 * @param outputFile
 */
void process(ifstream& file, Table symLitTable, ofstream& outputFile) {
    string line, recordStart, progEnd, name;
    string base = "";
    int addr = 0;

    // placing Symbols into sorted order
    list<int> remainingSymbols;
    for (auto &symbol : symLitTable.symbolMap) {
        remainingSymbols.push_back(hexToDecimal(symbol.first));
    }
    remainingSymbols.sort();

    // placing Literals into sorted order
    list<int> remainingLiterals;
    for (auto &literal : symLitTable.literalMap) {
        remainingLiterals.push_back(hexToDecimal(literal.first));
    }
    remainingLiterals.sort();

    // header
    std::getline(file, line);
    progEnd = buildHeader(line, name, outputFile);

    // parsing through obj code
    while (std::getline(file, line)) {
        if (line[0] == 'T') { // Text Record found
            recordStart = line.substr(1, 6); // startAddr

            // when record skips symbol addressing
            accountSymbols(addr, recordStart, remainingSymbols, symLitTable, outputFile);

            // using record BYTE length to calc DIGIT length, 1 byte = 2 digits
            int digits = hexToDecimal(string(1, line[7]) + line[8]) * 2;

            line = line.substr(9); // pull objCode
            while (digits > 0) {
                string hexAddr = formatHex(decimalToHex(addr), 6);
                literal curLit = symLitTable.literalMap[hexAddr];

                if (!curLit.constant.empty()) { // check if literal @ hexAddr exists
                    buildLiteral(addr, curLit, outputFile);
                    remainingLiterals.pop_front(); // lit used, pop

                    line = line.substr(curLit.length);
                    digits -= curLit.length;
                } else {
                    Instruction instr = Instruction(&line, addr);
                    if (addr == remainingSymbols.front()) {
                        remainingSymbols.pop_front(); // sym used, pop
                    }
                    buildInstruction(instr, addr, symLitTable, base, outputFile);

                    digits -= instr.objCode.length();
                }
            }
        }
    }

    // ensuring all symbols addressed before end
    accountSymbols(addr, progEnd, remainingSymbols, symLitTable, outputFile);

    buildEnd(name, outputFile);
}

int main(int argc, char** argv) {
    ifstream sym, program;
    ofstream output;
    string symFilename, progFilename;

    // command-line argument checking
    if(argc == 3) {
        progFilename = argv[1];
        symFilename = argv[2];
    }
    else {
        std::cout << "Usage: ./disassem test.obj test.sym" << std::endl;
        return 1;
    }

    // Parse SYMTAB and LITTAB tables
    sym.open(symFilename);
    Table symLitTable = Table(sym);

    sym.close();

    // Parsing machine code
    program.open(progFilename);
    output.open("out.lst");
    process(program, symLitTable, output);

    program.close();
    output.close();

    return 0;
}

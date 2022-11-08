//
// Created by Anthony Norderhaug on 11/6/22.
//

#ifndef INC_530PROGRAM2_TABLE_H
#define INC_530PROGRAM2_TABLE_H

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Instruction.h"
#include "Formatting.h"

using namespace std;

class Table {
    public:
        map<string, string> symbolMap;
        map<string, literal> literalMap;

        Table(ifstream& file) {
            symbolMap = initSymbols(file);
            literalMap = initLiterals(file);
        }
    private:
        map<string, string> initSymbols(ifstream& file);
        map<string, literal> initLiterals(ifstream& file);
};

#endif //INC_530PROGRAM2_TABLE_H

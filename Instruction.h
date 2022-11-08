//
// Created by Anthony Norderhaug on 11/1/22.
//

#ifndef INC_530PROGRAM2_INSTRUCTION_H
#define INC_530PROGRAM2_INSTRUCTION_H

#include <string>
#include <map>
#include <algorithm>
#include "Conversion.h"
#include "Library.h"

using namespace std;

struct literal {
    string symbol;
    string constant;
    int length;
};

class Instruction {
    public:
        string* record;
        map<string, string> addressingModes = {
                {"TAAM", ""},
                {"OAM", ""}
        };

        int addr;
        string binaryOpcode, opcode, mnemonic;
        string nixbpe;
        string objCode;

        int format;
        int length;

        Instruction(std::string* current, int currAddr);

        void initOpcode();
        void initFormat();
        void initSource();
        void initAddressing();
};

#endif //INC_530PROGRAM2_INSTRUCTION_H

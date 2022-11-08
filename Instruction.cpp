/**
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * Instruction.cpp => Instruction initialization
 */

#include "Instruction.h"

using std::string; using std::stringstream; using namespace Library;

/**
 * Constructor for an Instruction object
 *
 * @param current           active record
 * @param addr
 */
Instruction::Instruction(std::string* current, int addr) {
    record = current;
    this->addr = addr;

    // initialization
    initOpcode();
    initFormat();
    initSource();
    initAddressing();
}

/**
 * initOpcode() pulls opcode and substitutes "00" into last 2 digits
 */
void Instruction::initOpcode() {
    // pulling opCode and substituting "00" for final 2 digits
    opcode = (*record).substr(0,2);
    binaryOpcode = hexToBinary(string(1, opcode[0])) + hexToBinary(string(1, opcode[1]));
    opcode = opcode[0] + binaryToHex({binaryOpcode[4], binaryOpcode[5], '0', '0'});

    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
}

/**
 * initFormat() deciphers instruction format and bit length
 */
void Instruction::initFormat() {
    if (format2.find(opcode) != format2.end()) { // format 2
        format = 2;
        length = 16;
        mnemonic = format2[opcode];
    } else {
        mnemonic = format3and4[opcode];
        nixbpe = binaryOpcode.substr(6, 8) + hexToBinary(string(1, (*record)[2]));

        if (nixbpe[5] == '1') { // format 4
            format = 4;
            length = 32;
        } else { // format 3
            format = 3;
            length = 24;
        }
    }
}

/**
 * initSource() pulls objCode and updastes active record
 */
void Instruction::initSource() {
    objCode = (*record).substr(0, length/4); // pulling object code
    *record = (*record).substr(length/4); // reducing record length
}

/**
 * initAddressing() deciphers addressing modes
 */
void Instruction::initAddressing() {
    // OAM
    if (nixbpe[0] != nixbpe[1]) {
        if (nixbpe[0] == '1') {
            addressingModes["OAM"] = "indirect";
        } else {
            addressingModes["OAM"] = "immediate";
        }
    }

    // TAAM
    if (nixbpe[3] == '1') {
        addressingModes["TAAM"] = "base relative";
    } else if (nixbpe[4] == '1') {
        addressingModes["TAAM"] = "pc relative";
    }

    if (nixbpe[2] == '1') {
        addressingModes["TAAM"] += ", indexed";
    }
}
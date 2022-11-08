/**
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * Disassembly.cpp => translating machine code into SIC/XE assembly
 */

#include "Disassembly.h"

using namespace Library;

/**
 * output() organizes instruction into SIC/XE assembly format
 *
 * @param addr
 * @param label
 * @param mnemonic
 * @param operand
 * @param objCode
 * @param outputFile
 */
void output(string addr, string label, string mnemonic,
            string operand, string objCode, ofstream& outputFile) {
    outputFile << spacing(addr) +
            spacing(label) +
            spacing(mnemonic) +
            spacing(operand) +
            spacing(objCode) << endl;
}

/**
 * deriveTA() finds target address according to base, addressing modes, and
 * instruction format
 *
 * @param instr
 * @param base
 * @return                   target address
 */
string deriveTA(Instruction instr, string base) {
    string targetAddress;
    string OAM = instr.addressingModes["OAM"];
    string TAAM = instr.addressingModes["TAAM"];

    if (instr.format == 2) {
        return instr.objCode.substr(2, 1); // 3rd digit to pull register
    } else if (instr.format == 3 || OAM.find("immediate") == string::npos) {
        // "immediate" not affected by pc or base addressing

        if (TAAM.find("pc relative") != string::npos) {
            return decimalToHex(int(hexToDecimal(instr.objCode.substr(3)) +
                                    (instr.addr + instr.format)) % 4096);

        } else if (TAAM.find("base relative") != string::npos && !base.empty()) {
            return decimalToHex(int(hexToDecimal(instr.objCode.substr(3)) + hexToDecimal(base)));
        }
    }
    return instr.objCode.substr(3);
}

/**
 * buildHeader() pulls program name, starting address, and end
 *
 * @param record
 * @param progName
 * @param outputFile
 * @return
 */
string buildHeader(string record, string &progName, ofstream& outputFile) {
    string start, end, name;
    name = record.substr(1, 6);
    start = record.substr(9, 4);
    end = formatHex(record.substr(13, 6), 6);

    output(
            start,
            name,
            "START",
            "0",
            "",
            outputFile);

    progName = name;
    return end;
}

void buildBase(string symbol, ofstream& outputFile) {
    output("", "", "BASE", symbol, "", outputFile);
}

/**
 * buildSymbol() reserves space for variables in SYMTAB
 *
 * @param addr
 * @param symbol
 * @param distance              distance to next address
 * @param outputFile
 */
void buildSymbol(int &addr, string symbol, int distance, ofstream& outputFile) {
    output(
            formatHex(decimalToHex(addr), 4),
            symbol,
            "RESB",
            to_string(distance), // distance to targetAddr
            "",
            outputFile
    );

    addr += distance;
}

/**
 * buildLiteral() outputs assembly for literal definition, considers label presence
 *
 * @param addr
 * @param val
 * @param outputFile
 */
void buildLiteral(int &addr, literal val, ofstream& outputFile) {
    string objCode = val.constant;
    // removing '=', ''', and 'X'  for objCode
    if (objCode[0] == '=') { // literal
        objCode = objCode.substr(3);
    } else { // constant
        objCode = objCode.substr(2);
    }
    objCode.resize(objCode.size()-1);

    // if literal (outside instr) detected with no symbol, begin grouping
    if (val.symbol.empty()) {
        output("", "", "LTORG", "", "", outputFile);
    }

    output(
            formatHex(decimalToHex(addr), 4),
            val.symbol,
            val.symbol.empty() ? "*" : "BYTE",
            val.constant,
            objCode,
            outputFile
    );

    addr += objCode.length()/2;
}

/**
 * buildinstruction outputs assembly for instructions.
 * Format of (addr, label, mnemonic, operand, objCode)
 *
 * @param instr
 * @param curAddr
 * @param symLit
 * @param baseHex
 * @param outputFile
 */
void buildInstruction(Instruction instr, int& curAddr, Table symLit,
                      string& baseHex, ofstream& outputFile) {
    string addr, label, mnemonic, operand, objCode;
    string addrKey, opKey, opCopy;

    // 1. Address
    addr = formatHex(decimalToHex(curAddr), 4);

    // 2. Label
    addrKey = formatHex(decimalToHex(curAddr), 6);
    label = (curAddr != 0) ? symLit.symbolMap[addrKey] : "FIRST";

    if (label.empty() && symLit.literalMap.find(addrKey) != symLit.literalMap.end()) { // no sym, literal found
        label = symLit.literalMap[addrKey].symbol;
    }

    // 3. Mnemonic
    if (instr.format == 4) {
        mnemonic = "+" + instr.mnemonic;
    } else {
        mnemonic = instr.mnemonic;
    }

    // 4. Operand
    string targetAddress = deriveTA(instr, baseHex);
    opKey = formatHex(targetAddress, 6);

    if (instr.format == 4 && !symLit.literalMap[opKey].constant.empty()) { // FORMAT 4 && LITERAL @ TA
        operand = symLit.literalMap[opKey].constant;

    } else if (!symLit.literalMap[addrKey].constant.empty()) { // LITERAL @ ADDR
        operand = symLit.literalMap[addrKey].constant;

    } else { // no literals detected, focus on SYMBOLS & CONSTANTS
        if (mnemonic == "CLEAR") {
            operand = registers[stoi(targetAddress)];
        } else if (!symLit.symbolMap[opKey].empty()) { // SYMBOL found
            operand = symLit.symbolMap[opKey];
        } else if (!symLit.literalMap[opKey].symbol.empty()) { // CONSTANT found
            operand = symLit.literalMap[opKey].symbol;
        } else {
            operand = to_string(hexToDecimal(targetAddress)); // use targetAddress
        }
    }

    // Applying addressing modes onto Operand
    string OAM = instr.addressingModes["OAM"];
    string TAAM = instr.addressingModes["TAAM"];
    opCopy = operand;

    if (instr.format != 2) { // not applicable for registers i.e. format 2
        if (OAM.find("immediate") != string::npos && mnemonic != "CLEAR") {
            operand = "#" + operand;
        }
        if (OAM.find("indirect") != string::npos) {
            operand = "@" + operand;
        }
        if (TAAM.find("indexed") != string::npos) {
            operand += ",X";
        }
    }

    // 5. Object Code
    // Output instruction
    output(addr, label, mnemonic, operand, instr.objCode, outputFile);

    // Update address
    curAddr += instr.format;

    // If Base loaded, include Base instr
    if (instr.mnemonic == "LDB") {
        buildBase(opCopy, outputFile);
        baseHex = formatHex(targetAddress, 6);
    }
}

void buildEnd(string name, ofstream& outputFile) {
    output("", "", "END", name, "", outputFile);
}
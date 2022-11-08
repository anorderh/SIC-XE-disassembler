/**
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * Library.cpp => Opcodes and registers
 */

#include "Library.h"

map<string, string> Library::format2 = {
        {"90", "ADDR"},
        {"B4", "CLEAR"},
        {"A0", "COMPR"},
        {"9C", "DIVR"},
        {"98", "MULR"},
        {"AC", "RMO"},
        {"A4", "SHIFTL"},
        {"A8", "SHIFTR"},
        {"94", "SUBR"},
        {"B0", "SVC"},
        {"B8", "TIXR"},
};

map<string, string> Library::format3and4 = {
        {"18", "ADD"},{"58", "ADDF"},{"48", "AND"},{"28", "COMP"},
        {"88", "COMPF"},{"24", "DIV"},{"64", "DIVF"},{"3C", "J"},
        {"30", "JEQ"},{"34", "JGT"},{"38", "JLT"},{"48", "JSUB"},
        {"00", "LDA"},{"68", "LDB"},{"50", "LDCH"},{"70", "LDF"},
        {"08", "LDL"},{"6C", "LDS"},{"74", "LDT"},{"04", "LDX"},
        {"D0", "LPS"},{"20", "MUL"},{"60", "MULF"},{"44", "OR"},
        {"D8", "RD"},{"4C", "RSUB"},{"EC", "SSK"},{"0C", "STA"},
        {"78", "STB"},{"54", "STCH"},{"80", "STF"},{"D4", "STI"},
        {"14", "STL"},{"7C", "STS"},{"E8", "STSW"},{"84", "STT"},
        {"10", "STC"},{"1C", "SUB"},{"5C", "SUBF"},{"E0", "TD"},
        {"2C", "TIX"},{"DC", "WD"},
};

map<int, string> Library::registers = {
        {0, "A"},
        {1, "X"},
        {2, "L"},
        {3, "B"},
        {4, "S"},
        {5, "T"},
        {6, "F"},
        {8, "PC"},
        {9, "SW"},
};
/**
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * Conversion.cpp => translating hex, decimal, and binary
 */

#include "Conversion.h"

using namespace std;

std::string decimalToBinary(int decimal) {
    return std::bitset<4>(decimal).to_string();
}

long binaryToDecimal(std::string binary) {
    return std::bitset<8>(binary).to_ulong();
}

std::string decimalToHex(int decimal) {
    std::stringstream res;

    res << std::hex << decimal;
    return res.str();
}

long hexToDecimal(std::string hexStr) {
    std::stringstream res;
    int x;

    res << std::hex << hexStr;
    res >> x;
    return x;
}

std::string binaryToHex(std::string binary) {
    return decimalToHex(binaryToDecimal(binary));
}

std::string hexToBinary(std::string hexStr) {
    return decimalToBinary(hexToDecimal(hexStr));
}
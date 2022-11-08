/*
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * Conversion.h => helpers for hex, binary, and decimal
 */

#ifndef Conversion_h
#define Conversion_h

#include <bitset>
#include <sstream>
#include <string>

std::string decimalToBinary(int decimal);
long binaryToDecimal(std::string binary);

std::string decimalToHex(int decimal);
long hexToDecimal(std::string hexStr);

std::string binaryToHex(std::string binary);
std::string hexToBinary(std::string hexStr);

#endif

//
// Created by Anthony Norderhaug on 11/6/22.
//

#ifndef INC_530PROGRAM2_FORMATTING_H
#define INC_530PROGRAM2_FORMATTING_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> split(string line, char delimiter);
string spacing(string input);
string formatHex(string hexAddr, int spaced);

#endif //INC_530PROGRAM2_FORMATTING_H

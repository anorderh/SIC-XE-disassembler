/**
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * Table.cpp => parsing SYMTAB / LITTAB and Table initialization
 */

#include "Table.h"

using namespace std;

/**
 * initSymbols() maps all respective addresses to their symbols
 *
 * @param file
 * @return              mapped symbols
 */
map<string, string> Table::initSymbols(ifstream& file) {
    map<string, string> table;
    vector<string> entries;
    string line;

    // parsing line-by-line
    while (std::getline(file, line)) {

        if (line.empty() || line.find("Lit_Const") != string::npos) {
            // Lit_Const indicates literal table reached, exit
            break;
        } else if (line.find('-') == string::npos && line.find(':') == string::npos) {
            // ':' and '-' indicate headers, exit
            entries = split(line, ' ');
            string sorted[entries.size()];
            std::copy(entries.begin(), entries.end(), sorted);

            if (sorted[0] != "FIRST") { // excluding FIRST
                table[sorted[1]] = sorted[0]; // mapping ADDR to SYMBOL
            }
        }
    }
    return table;
}

/**
 * initLiterals() maps all respective addresses to their constants and literals
 *
 * @param file
 * @return              mapped constants & literals
 */
map<string, literal> Table::initLiterals(ifstream& file) {
    map<string, literal> table;
    vector<string> entries;
    string line;

    // parsing line-by-line
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        } else if (line.find('-') == string::npos && line.find(':') == string::npos) {
            // ':' and '-' indicate headers, exit
            entries = split(line, ' ');
            string sorted[entries.size()];
            std::copy(entries.begin(), entries.end(), sorted);

            // mapping ADDR to LITERAL OBJ (symbol blank if not offered)
            if (entries.size() != 4) { // literal detected
                literal val = {"", sorted[0], stoi(sorted[1])};
                table[sorted[2]] = val;
            } else { // constant detected
                table[sorted[3]] = {sorted[0], sorted[1], stoi(sorted[2])};
            }
        }
    }
    return table;
}
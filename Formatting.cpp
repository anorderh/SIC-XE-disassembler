/**
 * CS 530 - B.Shen
 * Anthony Norderhaug, RedID: 823899304
 * Formatting.cpp => string manipulation to be readable
 */

#include "Formatting.h"

using namespace std;

/**
 * split() seperates input string into vector<string>, according to delimiter
 *
 * @param line
 * @param delimiter             char discerning splits' loc
 * @return
 */
vector<string> split(string line, char delimiter) {
    vector<string> contents;
    stringstream stream(line);
    string entry;

    while (getline(stream, entry, delimiter)) {
        if(!entry.empty()) {
            contents.push_back(entry);
        }
    }

    return contents;
}

/**
 * spacing() gives input length of 12 characters
 *
 * @param input
 * @return
 */
string spacing(string input) {
    int length = int(input.length());

    for (int j = (12 - length); j > 0; j--) {
        input += " ";
    }
    return input;
}

/**
 * formatHex() gives input length of "spaced" characters, fills with '0'
 *
 * @param hexAddr
 * @param spaced                int indicating output length
 * @return
 */
string formatHex(string hexAddr, int spaced) {
    transform(hexAddr.begin(), hexAddr.end(), hexAddr.begin(), ::toupper);
    int length = int(hexAddr.length());

    // spaced is hexAddr's desired length
    for (int j = (spaced - length); j > 0; j--) {
        hexAddr = "0" + hexAddr;
    }
    return hexAddr;
}
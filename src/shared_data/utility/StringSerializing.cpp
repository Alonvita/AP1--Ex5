//
// Created by alonv on 12/29/2017.
//

#include <algorithm>
#include "StringSerializing.h"

/**
 * split(const std::string &str, char delim).
 *
 * @param str string -- a string to split.
 * @param delim char -- a char as delimiter
 *
 * @return a vector representing the split string
 */
std::vector<std::string> split(const std::string &str, char delim) {
    // Local variables
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> tokens;

    // parse
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }

    return tokens;
}

/**
 * intToString(int n).
 *
 * @param n int -- an integer.
 *
 * @return a string representing this int.
 */
std::string intToString(int n) {
    // Local variables
    std::ostringstream convert;

    convert << n;

    return convert.str();
}

/**
 * clearAndCheckString(char* msg, int size).
 *
 * @param msg char* -- a message.
 * @param size int -- the size of the message.
 */
std::string clearAndCheckString(char msg[], int size) {
    // Local Variables
    char retVal[1024] = {0};
    std::string str;

    for(int i = 0; i < size; ++i) {
        if (msg[i] == '\n') {
            retVal[i] = '\0';
            str = retVal;
            return str;
        }

        if(!((msg[i] >= 'A' && msg[i] <= 'Z')
                || (msg[i] >= 'a' && msg[i] <= 'z')
                || (msg[i] == ' ')
                || (msg[i] >= '0' && msg[i] <= '9')
                || (msg[i] == ','))) {
            return "Unknown Command";
        }

        retVal[i] = msg[i];
    }
}
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Utils {
public:
    string getLinie();
    bool inputEmpty(const string &input);
    bool containsDigits(const string &input);
    bool containsSpaces(const string &input);
    bool validateMinLength(const string &input, const int minLength);
};

#endif // UTILS_H

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "Type.h"

using namespace std;

class Utils {
public:
    static char readCharacter();
    static string readLine();
    static bool validateInput(const string &input, FieldType inputType);
    static bool inputEmpty(const string &input);
    static bool containsOnlyLetters(const string &input);
    static bool containsSpaces(const string &input);
    static bool correctLength(const string &input, const int minLength, const int maxLength);
    static string upperFirstLowerRest(string &input);

};

#endif // UTILS_H

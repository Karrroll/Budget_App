#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <regex>
#include <cmath>
#include <sstream>
#include <iomanip>

#include "Type.h"

using namespace std;

class Utils {
public:
    static char readCharacter();
    static string readLine();

    static bool isValidAmount(const string &amount);
    static double parseAmount(const string &input);
    static string formatAmount(const double &amount);

    static bool validateInput(const string &input, UserFieldType inputType);
    static bool inputEmpty(const string &input);
    static bool containsOnlyLetters(const string &input);
    static bool containsSpaces(const string &input);
    static bool correctLength(const string &input, const int minLength, const int maxLength);
    static string upperFirstLowerRest(string &input);
};

#endif // UTILS_H

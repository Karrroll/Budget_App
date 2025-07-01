#ifndef DATEMETHODS_H
#define DATEMETHODS_H

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <conio.h>

#include "Utils.h"
#include "Menus.h"

using namespace std;

class DateMethods {
private:
    static bool isYearLeap(const int year);
    static bool isDataFormatValid(const string &date);
    static bool isDateRangeValid(const string &date);
    static bool confirmDate(const string &date);
    static string convertToNoDashesDate(const string &date);

public:
    static string selectDate();
    static int getDaysInMonth(const int year, const int month);
    static bool validateDate(const string &date);
    static string getTodayDate();
    static string getUserSelectedDate();
    static string convertToDateWithDashes(const string &date);
    static int convertStringDateToInt(const string &dateStr);
};

#endif // DATEMETHODS_H

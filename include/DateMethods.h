#ifndef DATEMETHODS_H
#define DATEMETHODS_H

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <conio.h>

using namespace std;

class DateMethods {
public:
    bool validateDate(const string &date);
    bool isYearLeap(const int year);
    bool isDataFormatValid(const string &date);
    bool isDateRangeValid(const string &date);
    string getTodayDate();
    string getUserSelectedDate();
    int convertStringDateToInt(const string &dateStr);
protected:

private:
};

#endif // DATEMETHODS_H

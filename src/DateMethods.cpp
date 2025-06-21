#include "DateMethods.h"

string DateMethods::selectDate() {
    cout << "Press ENTER to use today's date or any other button to custom choose date: " << endl;
    char choose = getch();

    if (choose == '\r')
        return getTodayDate();
    else
        return getUserSelectedDate();
}

int DateMethods::getDaysInMonth(const int year, const int month) {
    int maxDaysInMonth = 31;

    switch(month) {
        case 4: case 6: case 9: case 11:
            maxDaysInMonth = 30;
            break;
        case 2:
            if (isYearLeap(year))
                maxDaysInMonth = 29;
            else
                maxDaysInMonth = 28;
            break;
    }

    return maxDaysInMonth;
}

bool DateMethods::validateDate(const string &date) {
    return (isDataFormatValid(date) && isDateRangeValid(date));
}

bool DateMethods::isYearLeap(const int year) {
    return ((year%4 == 0 && year%100 != 0) || (year%400 == 0));
}

bool DateMethods::isDataFormatValid(const string &date) {
    if (date.length() == 8) {
        for (char sign: date) {
            if (!isdigit(sign))
                return false;
        }
        return true;
    }

    cout << "Invalid date format." << endl;
    system("pause");
    return false;
}

bool DateMethods::isDateRangeValid(const string &date) {
    const int MIN_YEAR = 2000;
    const int MIN_MONTH = 1;
    const int MAX_MONTH = 12;
    const int MIN_DAY = 1;

    int year = stoi(date.substr(0,4));
    int month = stoi(date.substr(4,2));
    int day = stoi(date.substr(6,2));
    string currentDate = getTodayDate();

    if (year < MIN_YEAR || date > currentDate) {
        cout << "Invalid date. Date must be between 2000-01-01 and " << dateWithDashes(currentDate) << ". Try again." << endl;
        system("pause");
        return false;
    }

    if (month < MIN_MONTH || month > MAX_MONTH) {
        cout << "Invalid date. Month is out of range for the selected date. Try again." << endl;
        system("pause");
        return false;
    }

    int lastDayOfMonth = getDaysInMonth(year, month);
    if (day < MIN_DAY || day > lastDayOfMonth) {
        cout << "Invalid date. Day is out of range for the selected date. Try again." << endl;
        system("pause");
        return false;
    }

    return true;
}

string DateMethods::getTodayDate() {
    ostringstream todayDate;

    time_t currentTime = time(0);
    tm *date = localtime(&currentTime);

    todayDate << setfill('0') << setw(4) << date->tm_year + 1900 << setw(2) << date->tm_mon + 1 << setw(2) << date->tm_mday;

    return todayDate.str();
}

string DateMethods::getUserSelectedDate() {
    string dateTemplate = "yyyy-mm-dd";
    string userDate = dateTemplate;
    string userDateStr = "";

    size_t i = 0;
    while (i < userDate.length()) {
        if (userDate[i] == '-') {
            i++;
            continue;
        }

        cout << "\rEnter date: " << userDate << flush;
        char input = getch();

        if (input == '\b' && i > 0) {
            do {
                i--;
            } while (i > 0 && userDate[i] == '-');

            userDate[i] = dateTemplate[i];
            userDateStr.pop_back();
            continue;
        }

        if (!isdigit(input))
            continue;

        userDate[i] = input;
        userDateStr += input;
        i++;
    }

    cout << endl;
    if (!validateDate(userDateStr) || !confirmDate(userDate))
        userDateStr = "0";

    return userDateStr;
}

bool DateMethods::confirmDate(const string &date) {
    cout << "Press (y) to confirm or (n) to reject date: " << date << endl;
    char userChoice = Utils::readCharacter();

    if (userChoice == 'y' || userChoice == 'Y')
        return true;

    return false;
}

string DateMethods::dateWithDashes(const string &date) {
    return date.substr(0, 4) + "-" + date.substr(4, 2) + "-" + date.substr(6, 2);
}

int DateMethods::convertStringDateToInt(const string &dateStr) {
    return stoi(dateStr);
}

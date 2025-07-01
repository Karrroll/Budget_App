#include "DateMethods.h"

bool DateMethods::isYearLeap(const int year) {
    return ((year%4 == 0 && year%100 != 0) || (year%400 == 0));
}

bool DateMethods::isDataFormatValid(const string &date) {
    if (date.length() != 8) {
        cout << "\nInvalid date format." << endl;
        system("pause");
        return false;
    }

    for (char sign: date) {
        if (!isdigit(sign)) {
            cout << "\nInvalid date format. Only digit allowed." << endl;
            system("pause");
            return false;
        }
    }

    return true;
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
        cout << "\nInvalid date. Date must be between 2000-01-01 and " << convertToDateWithDashes(currentDate) << " ." << endl;
        system("pause");
        return false;
    }

    if (month < MIN_MONTH || month > MAX_MONTH) {
        cout << "\nInvalid date. Month is out of range for the selected date." << endl;
        system("pause");
        return false;
    }

    int lastDayOfMonth = getDaysInMonth(year, month);
    if (day < MIN_DAY || day > lastDayOfMonth) {
        cout << "\nInvalid date. Day is out of range for the selected date." << endl;
        system("pause");
        return false;
    }

    return true;
}

bool DateMethods::confirmDate(const string &date) {
    cout << "\nPress (y) to confirm or (n) to reject date: " << convertToDateWithDashes(date) << endl;
    char userChoice = Utils::readCharacter();

    if (userChoice == 'y' || userChoice == 'Y')
        return true;

    return false;
}

string DateMethods::convertToNoDashesDate(const string &date) {
    string noDashesDate = date;
    noDashesDate.erase(remove(noDashesDate.begin(), noDashesDate.end(), '-'), noDashesDate.end());

    return noDashesDate;
}

string DateMethods::selectDate() {
    while (true) {
        Menus::showMenu(MenuType::DATE_SELECTION_MENU);
        char userChoice = Utils::readCharacter();

        switch (userChoice) {
            case '1':
                return getTodayDate();
            case '2':
                return getUserSelectedDate();
            default:
                cout << "\nInvalid choice. Please try again." << endl;
                system("pause");
                break;
        }
    }
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

string DateMethods::getTodayDate() {
    ostringstream todayDate;

    time_t currentTime = time(0);
    tm *date = localtime(&currentTime);

    todayDate << setfill('0') << setw(4) << date->tm_year + 1900 << setw(2) << date->tm_mon + 1 << setw(2) << date->tm_mday;

    return todayDate.str();
}

string DateMethods::getUserSelectedDate() {
    cout << "\nPlease enter the date (YYYY-MM-DD): ";
    string userDate = Utils::readLine();

    if (userDate[4] != '-' || userDate[7] != '-') {
        cout << "\nInvalid date format." << endl;
        system("pause");
        return "0";
    }

    string noDashesDate = convertToNoDashesDate(userDate);

    if (!validateDate(noDashesDate) || !confirmDate(noDashesDate))
        return "0";

    return noDashesDate;
}

string DateMethods::convertToDateWithDashes(const string &date) {
    return date.substr(0, 4) + "-" + date.substr(4, 2) + "-" + date.substr(6, 2);
}

int DateMethods::convertStringDateToInt(const string &dateStr) {
    return stoi(dateStr);
}

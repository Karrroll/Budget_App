#include "DateMethods.h"

string DateMethods::getTodayDate() {
    string currentDateString = "";
    ostringstream todayDate;

    time_t currentTime = time(0);
    tm *date = localtime(&currentTime);

    todayDate << setw(4) << date->tm_year + 1900 << setw(2) << setfill('0') << date->tm_mon + 1 << setw(2) << setfill('0') << date->tm_mday;

    cout << todayDate.str() << endl;
    return currentDateString;
}



time_t aktualnyCzas = time(0);      //pobiera czas w sekundach od 1970 (0) czyli tylko zwraca nie zapisuje do wskaŸnika

tm *data = localtime(&aktualnyCzas);        // rozbija na strukture czasu lokalnego lokaltime oczekuje wskaŸnik i zapisuje do wkaŸnika tm przez co mam do niego potem dostêp w innych metodach aby wyci¹gn¹c date/godzine itd

cout << data -> tm_year << endl;
cout << data -> tm_mon << endl;
cout << data -> tm_mday << endl;
cout << data -> tm_hour << endl;
cout << data -> tm_min << endl;
cout << data -> tm_sec << endl;
cout << data -> tm_isdst << endl;
cout << data -> tm_wday << endl;
cout << data -> tm_yday << endl;        // wszytsko to int


ostringstream dzisiejszaData;

dzisiejszaData << setw(4) << setfill('0') << data -> tm_year + 1900 << "-" << setw(2) << setfill('0') << data -> tm_mon + 1 << "-" << setw(2) << setfill('0') << data -> tm_mday;

cout << dzisiejszaData.str() << endl;

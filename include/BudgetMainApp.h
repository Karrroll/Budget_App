#ifndef BUDGETMAINAPP_H
#define BUDGETMAINAPP_H

#include <iostream>

using namespace std;

class BudgetMainApp {
    const string INCOME_FILE_NAME;
    const string EXPENSE_FILE_NAME;

public:
    BudgetMainApp(string userFileName, string incomeFileName, string expenseFileName) : INCOME_FILE_NAME(incomeFileName), EXPENSE_FILE_NAME(expenseFileName) {};

};

#endif // BUDGETMAINAPP_H

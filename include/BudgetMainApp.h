#ifndef BUDGETMAINAPP_H
#define BUDGETMAINAPP_H

#include <iostream>

#include "UserManager.h"

using namespace std;

class BudgetMainApp {
private:
    UserManager userManager;
    const string INCOME_FILE_NAME;
    const string EXPENSE_FILE_NAME;

public:
    BudgetMainApp(const string &userFileName, const string &incomeFileName, const string &expenseFileName) : userManager(userFileName), INCOME_FILE_NAME(incomeFileName), EXPENSE_FILE_NAME(expenseFileName) {};

    bool isUserLoggedIn();
    void registerNewUser();
    void loginUser();
    void changeUserPassword();
    void logoutUser();
};

#endif // BUDGETMAINAPP_H

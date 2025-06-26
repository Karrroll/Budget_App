#ifndef BUDGETMAINAPP_H
#define BUDGETMAINAPP_H

#include <iostream>

#include "UserManager.h"
#include "TransactionManager.h"

using namespace std;

class BudgetMainApp {
private:
    UserManager userManager;
    TransactionManager *transactionManager;
    const string INCOME_FILE_NAME;
    const string EXPENSE_FILE_NAME;

public:
    BudgetMainApp(const string &userFileName, const string &incomeFileName, const string &expenseFileName);
    ~BudgetMainApp();

    bool isUserLoggedIn();
    void registerNewUser();
    void loginUser();
    void changeUserPassword();
    void logoutUser();
    void addIncome();
    void addExpense();
    void showCurrentMonthBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance();
};

#endif // BUDGETMAINAPP_H

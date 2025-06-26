#include "BudgetMainApp.h"

BudgetMainApp::BudgetMainApp(const string &userFileName, const string &incomeFileName, const string &expenseFileName) : userManager(userFileName), INCOME_FILE_NAME(incomeFileName), EXPENSE_FILE_NAME(expenseFileName) {
    transactionManager = nullptr;
}

BudgetMainApp::~BudgetMainApp() {
    delete transactionManager;
    transactionManager = nullptr;
}

bool BudgetMainApp::isUserLoggedIn() {
    return userManager.isUserLoggedIn();
}

void BudgetMainApp::registerNewUser() {
    system("cls");
    cout << "\t<<< CREATE NEW ACCOUNT >>>" << endl << endl;
    userManager.registerNewUser();
}

void BudgetMainApp::loginUser() {
    system("cls");
    cout << "\t<<< SIGN IN TO BUDGET APP >>>" << endl << endl;
    userManager.loginUser();

    transactionManager = new TransactionManager(userManager.getLoggedUserId(), INCOME_FILE_NAME, EXPENSE_FILE_NAME);
}

void BudgetMainApp::changeUserPassword() {
    system("cls");
    cout << "\t<<< UPDATE PASSWORD >>>" << endl << endl;
    userManager.changeUserPassword();
}

void BudgetMainApp::logoutUser() {
    userManager.logoutUser();
}

void BudgetMainApp::addIncome() {
    transactionManager->addTransaction(TransactionType::INCOME);
}

void BudgetMainApp::addExpense() {
    transactionManager->addTransaction(TransactionType::EXPENSE);
}
void BudgetMainApp::showCurrentMonthBalance() {
    transactionManager->showCurrentMonthBalance();
}

void BudgetMainApp::showPreviousMonthBalance() {
    transactionManager->showPreviousMonthBalance();
}

void BudgetMainApp::showCustomPeriodBalance() {
    transactionManager->showCustomPeriodBalance();
}

#include "BudgetMainApp.h"

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
    system("cls");
    cout << "\t<<< NEW INCOME >>>" << endl << endl;
    transactionManager->addIncome();
}

void BudgetMainApp::addExpense() {
    system("cls");
    cout << "\t<<< NEW EXPENSE >>>" << endl << endl;
    transactionManager->addExpense();
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

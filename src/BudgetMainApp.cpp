#include "BudgetMainApp.h"

bool BudgetMainApp::isUserLoggedIn() {
    return userManager.isUserLoggedIn();
}

void BudgetMainApp::registerNewUser() {
    userManager.registerNewUser();
}

void BudgetMainApp::loginUser() {
    userManager.loginUser();

    if (userManager.isUserLoggedIn())
        transactionManager = new TransactionManager(userManager.getLoggedUserId(), INCOME_FILE_NAME, EXPENSE_FILE_NAME);
}

void BudgetMainApp::changeUserPassword() {
    userManager.changeUserPassword();
}

void BudgetMainApp::logoutUser() {
    userManager.logoutUser();
}

void BudgetMainApp::addIncome() {
    transactionManager->addIncome();
}

void BudgetMainApp::addExpense() {
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

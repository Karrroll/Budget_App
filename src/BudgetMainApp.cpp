#include "BudgetMainApp.h"

bool BudgetMainApp::isUserLoggedIn() {
    return userManager.isUserLoggedIn();
}

void BudgetMainApp::registerNewUser() {
    userManager.registerNewUser();
}

void BudgetMainApp::loginUser() {
    userManager.loginUser();
}

void BudgetMainApp::changeUserPassword() {
    userManager.changeUserPassword();
}

void BudgetMainApp::logoutUser() {
    userManager.logoutUser();
}

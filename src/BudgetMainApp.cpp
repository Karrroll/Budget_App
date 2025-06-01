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

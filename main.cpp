#include <iostream>

#include "BudgetMainApp.h"

using namespace std;

int main() {
    BudgetMainApp budgetMainApp("users.xml", "incomes.xml", "expense.xml");

    while (true) {
        if (!budgetMainApp.isUserLoggedIn()) {
            char userChoice = '2';
//            userChoice =
            switch (userChoice) {
                case '1':
                    budgetMainApp.registerNewUser();
                    break;
                case '2':
                    budgetMainApp.loginUser();
                case '9':
                default:;
            }
        }
    }
}

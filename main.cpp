#include <iostream>

#include "BudgetMainApp.h"

using namespace std;

int main() {
    BudgetMainApp budgetMainApp("users.xml", "incomes.xml", "expense.xml");

    while (true) {
        if (!budgetMainApp.isUserLoggedIn()) {
            char userChoice = '1';
//            userChoice =
            switch (userChoice) {
                case '1':
                    budgetMainApp.registerNewUser();
                case '2':
                case '9':
                default:;
            }
        }
    }
}

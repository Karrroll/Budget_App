#include <iostream>

#include "BudgetMainApp.h"

using namespace std;

int main() {
    BudgetMainApp budgetMainApp("users.xml", "incomes.xml", "expense.xml");

    while (true) {
        if (budgetMainApp.isUserLoggedIn()) {

        }
    }
}

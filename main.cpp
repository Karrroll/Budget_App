#include <iostream>

#include "BudgetMainApp.h"

using namespace std;

int main() {
    BudgetMainApp budgetMainApp("users.xml", "incomes.xml", "expense.xml");

    while (true) {
        if (!budgetMainApp.isUserLoggedIn()) {
            char userChoice = Utils::readCharacter();

            switch (userChoice) {
                case '1':
                    budgetMainApp.registerNewUser();
                    break;
                case '2':
                    budgetMainApp.loginUser();
                    break;
                case '9':
                    cout << "Thank you for using the application. See you next time!" << endl;
                    system("pause");
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    }
    return 0;
}

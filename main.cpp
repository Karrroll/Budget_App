#include <iostream>

#include "BudgetMainApp.h"
#include "Menus.h"

using namespace std;

int main() {
    BudgetMainApp budgetMainApp("users.xml", "incomes.xml", "expenses.xml");

    while (true) {
        while (!budgetMainApp.isUserLoggedIn()) {

            Menus::showMenu(MenuType::MAIN_MENU);
            char userChoice = Utils::readCharacter();

            switch (userChoice) {
                case '1': budgetMainApp.registerNewUser();  break;
                case '2': budgetMainApp.loginUser();        break;
                case '9':
                    cout << "\nThank you for using the application. See you next time!" << endl;
                    return 0;
                default:
                    cout << "\nInvalid choice. Please try again." << endl;
                    system("pause");
                    break;
            }
        }

        while (budgetMainApp.isUserLoggedIn()) {
            Menus::showMenu(MenuType::USER_MENU);
            char userChoice = Utils::readCharacter();

            switch (userChoice) {
                case '1': budgetMainApp.addIncome();                break;
                case '2': budgetMainApp.addExpense();               break;
                case '3': budgetMainApp.showCurrentMonthBalance();  break;
                case '4': budgetMainApp.showPreviousMonthBalance(); break;
                case '5': budgetMainApp.showCustomPeriodBalance();  break;
                case '6': budgetMainApp.changeUserPassword();       break;
                case '7': budgetMainApp.logoutUser();               break;
                default:
                    cout << "\nInvalid choice. Please try again." << endl;
                    system("pause");
                    break;
            }
        }
    }
    return 0;
}

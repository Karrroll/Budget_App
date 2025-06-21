#include "Menus.h"

void Menus::showMainMenu() {
    cout << "1. Register User" << endl;
    cout << "2. Login User" << endl;
    cout << "9. Exit Application" << endl;
}

void Menus::showUserMenu() {
    cout << "1. Add Income" << endl;
    cout << "2. Add Expense" << endl;
    cout << "3. Show Current Month Balance" << endl;
    cout << "4. Show Last Month Balance" << endl;
    cout << "5. Show Custom Period Balance" << endl;
    cout << "6. Change Password" << endl;
    cout << "7. Logout" << endl;
}

void Menus::showMenu(MenuType menuType) {
    system("cls");

    switch (menuType) {
        case (MenuType::MAIN_MENU):
            cout << "\t<<< MAIN MENU >>>\n\n";
            showMainMenu();
            break;
        case (MenuType::USER_MENU):
            cout << "\t<<< USER MENU >>>\n" << endl;
            showUserMenu();
            break;
        default:
            cout << "Unknown menu type.\n" << endl;
            system ("pause");
            return;
    }
    cout << "\nEnter your choice:\t";
}

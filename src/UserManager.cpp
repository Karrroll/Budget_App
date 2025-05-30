#include "UserManager.h"

void UserManager::setLoggedUserId(const int id) {
    if (id > 0)
        this->loggedUserId = id;
}

void UserManager::registerNewUser() {
    userFile.addUserDataToFile(enterUserData());
}

void UserManager::loginUser() {
    int passwordAttemptsLeft = 3;
    string enteredLogin = "", enteredPassword = "";

    cout << "Enter login: ";
    enteredLogin = Utils::readLine();

    for (const auto &user : users) {
        if (user.userName == enteredLogin) {
            do {
                cout << "Enter password: ";
                enteredPassword = Utils::readLine();

                if (user.userPassword == enteredPassword) {
                    setLoggedUserId(user.id);
                    cout << "Hello " << enteredLogin << endl;
                    system("pause");
                    return;
                }

                passwordAttemptsLeft--;
                cout << "Invalid password. Attempts left: " << passwordAttemptsLeft << endl;
            } while (passwordAttemptsLeft > 0);

            cout << "Too many invalid attempts. Login failed." << endl;
            system("pause");
            return;
        }
    }
    cout << "User '" << enteredLogin << "' not found." << endl;
    system("pause");
}

User UserManager::enterUserData() {
    User user;

    user.id = userFile.getLastId() + 1;
    cout << "First Name: " ;
    while (!Utils::validateInput(user.firstName = Utils::readLine(), FieldType::FIRST_NAME)) {
        cout << "Try again." << endl;
    }
    Utils::upperFirstLowerRest(user.firstName);

    cout << "Last Name: ";
    while (!Utils::validateInput(user.lastName = Utils::readLine(), FieldType::LAST_NAME)) {
        cout << "Try again." << endl;
    }
    Utils::upperFirstLowerRest(user.lastName);

    cout << "Login: ";
    while (!Utils::validateInput(user.userName = Utils::readLine(), FieldType::LOGIN)) {
        cout << "Try again." << endl;
    }

    cout << "Password: ";
    while (!Utils::validateInput(user.userPassword = Utils::readLine(), FieldType::PASSWORD)) {
        cout << "Try again." << endl;
    }

    return user;
}


#include "UserManager.h"

void UserManager::setLoggedUserId(const int id) {
    if (id != this->loggedUserId && id > 0)
        this->loggedUserId = id;
}

bool UserManager::isUserLoggedIn() {
    return (getLoggedUserId() > 0);
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

User *UserManager::findUserById(const int id) {
    for (auto &user : users) {
        if (id == user.id)
            return &user;
    }
    return nullptr;
}

void UserManager::changeUserPassword() {
    int loggedUserId = getLoggedUserId();
    User *user = findUserById(loggedUserId);

    if (!user) {
        cout << "Password was not changed. User not found in '" << userFile.getFileName() << "' file." << endl;
        system("pause");
        return;
    }

    string enteredNewPassword = "";
    while (true) {
        cout << "Enter new password: ";
        enteredNewPassword = Utils::readLine();

        if (enteredNewPassword == user->userPassword) {
            cout << "New password cannot be the same as the current one." << endl;
            cout << "Try again." << endl;
            continue;
        }

        if (!Utils::validateInput(enteredNewPassword, FieldType::PASSWORD)) {
            cout << "Try again." << endl;
            continue;
        }

        if (!userFile.changePasswordInFile(user->id, enteredNewPassword)) {
            cout << "Failed to change password in file" << endl;
            system("pause");
            return;
        }

        user->userPassword = enteredNewPassword;
        cout << "Password changed successfully." << endl;
        system("pause");
        return;
    }
}

void UserManager::logoutUser() {
    setLoggedUserId(0);
    cout << "Logout successful" << endl;
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


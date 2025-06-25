#include "UserManager.h"

void UserManager::setLoggedUserId(const int id) {
    if (id != this->loggedUserId && id >= 0)
        this->loggedUserId = id;
}

bool UserManager::isUserLoggedIn() {
    return (getLoggedUserId() > 0);
}

bool UserManager::isLoginAvailable(const string &userName) {
    for (auto user : users) {
        if (userName == user.userName) {
            cout << "Login '" << userName << "' is already in use. Please choose another one." << endl << endl;
            return false;
        }
    }
    return true;
}

void UserManager::registerNewUser() {
    User newUser = enterUserData();

    if (!userFile.addUserDataToFile(newUser)) {
        cout << "\nUser registration failed." << endl;
        system("pause");
        return;
    }

    users.push_back(newUser);
    cout << "\nUser registered successfully." << endl;
    system("pause");
}

void UserManager::loginUser() {
    int passwordAttemptsLeft = 3;
    string enteredLogin = "", enteredPassword = "";

    cout << left << setw(12) << "Login:";
    enteredLogin = Utils::readLine();

    for (const auto &user : users) {
        if (user.userName == enteredLogin) {
            do {
                cout << left << setw(12) << "Password:";
                enteredPassword = Utils::readLine();

                if (user.userPassword == enteredPassword) {
                    setLoggedUserId(user.id);

                    if (isUserLoggedIn()) {
                        cout << "\nHello " << enteredLogin << "!" << endl;
                        system("pause");
                        return;
                    } else {
                        cout << "\nSign in failed." << endl;
                        system("pause");
                        return;
                    }
                }

                if (--passwordAttemptsLeft > 0)
                    cout << "\nInvalid password. Attempts left: " << passwordAttemptsLeft << endl;
            } while (passwordAttemptsLeft > 0);

            cout << "\nToo many invalid attempts. Sign in failed." << endl;
            system("pause");
            return;
        }
    }
    cout << "\nUser '" << enteredLogin << "' not found." << endl;
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
            cout << "New password cannot be the same as the current one." << endl << endl;
            continue;
        }

        if (!Utils::validateInput(enteredNewPassword, FieldType::PASSWORD))
            continue;

        if (!userFile.changePasswordInFile(user->id, enteredNewPassword)) {
            cout << "\nFailed to change password in file." << endl;
            system("pause");
            return;
        }

        user->userPassword = enteredNewPassword;
        cout << "\nPassword changed successfully." << endl;
        system("pause");
        return;
    }
}

void UserManager::logoutUser() {
    setLoggedUserId(0);
    cout << "\nLogout successful." << endl;
    system("pause");
}

User UserManager::enterUserData() {
    User user;

    user.id = userFile.getLastId() + 1;
    do {
        cout << left << setw(13) << "First Name:";
    } while (!Utils::validateInput(user.firstName = Utils::readLine(), FieldType::FIRST_NAME));

    do {
        cout << left << setw(13) << "Last Name:";
    } while (!Utils::validateInput(user.lastName = Utils::readLine(), FieldType::LAST_NAME));

    do {
        cout << left << setw(13) << "Login:";
    } while (!Utils::validateInput(user.userName = Utils::readLine(), FieldType::LOGIN) || !isLoginAvailable(user.userName));

    do {
        cout << left << setw(13) << "Password:";
    } while (!Utils::validateInput(user.userPassword = Utils::readLine(), FieldType::PASSWORD));

    Utils::upperFirstLowerRest(user.firstName);
    Utils::upperFirstLowerRest(user.lastName);

    return user;
}


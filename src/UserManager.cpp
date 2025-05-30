#include "UserManager.h"

void UserManager::setLoggedUserId(const int id) {
    if (id > 0)
        this->loggedUserId = id;
}

void UserManager::registerNewUser() {
    userFile.addUserDataToFile(enterUserData());
}

void UserManager::loginUser() {

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


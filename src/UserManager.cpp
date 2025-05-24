#include "UserManager.h"

User UserManager::enterUserData() {
    User user;
    string firstName = "", lastName = "", userName = "", userPassword = "";

//    user.id = file.getLastId()  // implementackja
    cout << "First Name: ";
    user.firstName = firstName;
    cout << "Last Name: ";
    user.lastName = lastName;
    cout << "Login: ";
    user.userName = userName;
    cout << "Password: ";
    user.userPassword = userPassword;

    return user;
}

void UserManager::registerNewUser() {

}

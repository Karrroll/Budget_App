#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>

#include "UserFile.h"
#include "Utils.h"

using namespace std;

class UserManager {
private:
    UserFile userFile;
    int loggedUserId;
    vector <User> users;

    User enterUserData();
    User *findUserById(const int id);
public:
    UserManager(const string &userFileName);

    int getLoggedUserId() const { return loggedUserId; };
    void setLoggedUserId(const int id);

    bool isUserLoggedIn();
    bool isLoginAvailable(const string &userName);
    void registerNewUser();
    void loginUser();
    void changeUserPassword();
    void logoutUser();
};

#endif // USERMANAGER_H

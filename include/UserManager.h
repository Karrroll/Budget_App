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

public:
    UserManager(const string &userFileName) : userFile(userFileName) {
        loggedUserId = 0;
        users = userFile.loadUsersFromFile();
    };

    int getLoggedUserId() const { return loggedUserId; };
    void setLoggedUserId(const int id);

    bool isUserLoggedIn(void);
    void registerNewUser();
    void loginUser();
};

#endif // USERMANAGER_H

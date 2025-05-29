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
    vector <User> users;

    User enterUserData();

public:
    UserManager(const string &userFileName) : userFile(userFileName) {
        users = userFile.loadUsersFromFile();
    };

    void registerNewUser();
};

#endif // USERMANAGER_H

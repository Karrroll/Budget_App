#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>

#include "UserFile.h"

using namespace std;

class UserManager {
    UserFile userFile;
    vector <User> users;
public:
    UserManager(const string &userFileName) : userFile(userFileName) {
        users = userFile.loadUsersFromFile();
    };

};

#endif // USERMANAGER_H

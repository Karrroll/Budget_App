#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
//#include <cstdlib>            //cls

#include "UserFile.h"
#include "Utils.h"

using namespace std;

class UserManager {
private:
    UserFile userFile;

    User enterUserData();
public:
    UserManager(const string &userFileName) : userFile(userFileName) {};

    void registerNewUser();
};

#endif // USERMANAGER_H

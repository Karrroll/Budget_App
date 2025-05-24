#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>

#include "File.h"
#include "User.h"

using namespace std;

class UserFile : public File {
public:
    UserFile(const string &userFileName) : File(userFileName, "Users", "User") {};

    bool addUserDataToFile(const User &user);

};

#endif // USERFILE_H

#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>

#include "File.h"

using namespace std;

class UserFile : public File {
public:
    UserFile(const string &userFileName) : File(userFileName, "Users", "User") {};


};

#endif // USERFILE_H

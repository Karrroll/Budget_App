#ifndef FILE_H
#define FILE_H

#include <iostream>

using namespace std;

class File {
    const string FILE_NAME;
public:
    File(const string &fileName) : FILE_NAME(fileName) {};

};

#endif // FILE_H

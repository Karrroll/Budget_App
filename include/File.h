#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include "Markup.h"

using namespace std;

class File {
private:
    const string FILE_NAME;

public:
    File(const string &fileName) : FILE_NAME(fileName) {};



protected:
    CMarkup xmlFile;
    bool isFileExist();

};

#endif // FILE_H

#include "File.h"

#include <iostream>

using namespace std;

bool File::isFileExist() {
    ifstream file(FILE_NAME);
    return file.good();
}

bool File::loadXmlFile(CMarkup &xmlFile) {
    if (!xmlFile.Load(FILE_NAME)) {
        cout << "Failed to load XML file: '" << FILE_NAME << "'" << endl;
        return false;
    }
    return true;
}

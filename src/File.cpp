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

bool File::enterXmlRootNode(CMarkup &xmlFile) {
    if (!xmlFile.FindElem(ROOT_NODE_NAME)) {
        cout << "Root node '" << ROOT_NODE_NAME << "' not found. Please verify '" << FILE_NAME << "' file format." << endl;
        return false;
    }
    xmlFile.IntoElem();
    return true;
}



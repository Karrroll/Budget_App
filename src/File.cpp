#include "File.h"

void File::setLastId(const int &id) {
    if (id > 0)
        lastId = id;
}

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

void File::createNewXmlFileWithRootNode(CMarkup &xmlFile) {
    xmlFile.AddElem(ROOT_NODE_NAME);
    xmlFile.Save(FILE_NAME);
}

void File::addChildNode(CMarkup &xmlFile) {
    xmlFile.AddElem(CHILD_NODE_NAME);
    xmlFile.IntoElem();
}

string File::getElementData(CMarkup &xmlFile, const string &elementName) {
    if (xmlFile.FindElem(elementName))
        return xmlFile.GetData();
    return "";
}

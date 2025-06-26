#include "File.h"

void File::setLastId(const int id) {
    if (id > 0)
        this->lastId = id;
}

bool File::isFileExist() {
    ifstream file(getFileName());
    return file.good();
}

bool File::loadXmlFile(CMarkup &xmlFile) {
    if (!xmlFile.Load(getFileName())) {
        cout << "\nFailed to load XML file: '" << getFileName() << "'" << endl;
        return false;
    }
    return true;
}

bool File::enterXmlRootNode(CMarkup &xmlFile) {
    if (!xmlFile.FindElem(getRootNodeName())) {
        cout << "\nRoot node '" << getRootNodeName() << "' not found. Please verify '" << getFileName() << "' file format." << endl;
        return false;
    }
    xmlFile.IntoElem();
    return true;
}

void File::createNewXmlFileWithRootNode(CMarkup &xmlFile) {
    xmlFile.AddElem(getRootNodeName());
    xmlFile.Save(getFileName());
}

bool File::addChildNode(CMarkup &xmlFile) {
    return xmlFile.AddElem(getChildNodeName()) && xmlFile.IntoElem();
}

string File::getElementData(CMarkup &xmlFile, const string &elementName) {
    if (xmlFile.FindElem(elementName))
        return xmlFile.GetData();
    return "";
}

#include "UserFile.h"

bool UserFile::addUserDataToFile(const User &user) {
    if (!isFileExist())
        createNewXmlFileWithRootNode();

    if (loadXmlFile() && enterXmlRootNode()) {
        addChildNode();

        xmlFile.AddElem("id", to_string(user.id));
        xmlFile.AddElem("firstName", user.firstName);
        xmlFile.AddElem("lastName", user.lastName);
        xmlFile.AddElem("login", user.userName);
        xmlFile.AddElem("password", user.userPassword);

        xmlFile.OutOfElem();
    } else {
        return false;
    }

    if (!xmlFile.Save(FILE_NAME)) {
        cout << "Failed to save the XML file: " << FILE_NAME << endl;
        return false;
    }
    return true;
}

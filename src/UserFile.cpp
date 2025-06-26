#include "UserFile.h"

bool UserFile::addUserDataToFile(const User &user) {
    CMarkup userXmlFile;
    if (!isFileExist())
        createNewXmlFileWithRootNode(userXmlFile);

    if (!loadXmlFile(userXmlFile) || !enterXmlRootNode(userXmlFile))
        return false;

    if (!addChildNode(userXmlFile))
        return false;

    userXmlFile.AddElem("id", to_string(user.id));
    userXmlFile.AddElem("firstName", user.firstName);
    userXmlFile.AddElem("lastName", user.lastName);
    userXmlFile.AddElem("login", user.userName);
    userXmlFile.AddElem("password", user.userPassword);

    userXmlFile.OutOfElem();

    if (!userXmlFile.Save(getFileName())) {
        cout << "Failed to save the XML file: " << getFileName() << endl;
        return false;
    }

    setLastId(user.id);
    return true;
}

bool UserFile::changePasswordInFile(const int userId, const string &newPassword) {
    CMarkup userXmlFile;

    if (!loadXmlFile(userXmlFile) || !enterXmlRootNode(userXmlFile))
        return false;

    while (userXmlFile.FindElem(getChildNodeName())) {
        userXmlFile.IntoElem();

        if (!userXmlFile.FindElem("id")) {
            userXmlFile.OutOfElem();
            cout << "\n<id> tag not found in node:" << endl << endl;
            cout << userXmlFile.GetSubDoc() << endl;
            cout << "Please check structure of '" << getFileName() << "' file." << endl;
            system("pause");
            return false;
        }

        int currentId = stoi(userXmlFile.GetData());
        if (currentId != userId) {
            userXmlFile.OutOfElem();
            continue;
        }

        if (!userXmlFile.FindElem("password")) {
            userXmlFile.OutOfElem();
            cout << "\n<password> tag not found in node:" << endl << endl;
            cout << userXmlFile.GetSubDoc() << endl;
            cout << "Please check structure of '" << getFileName() << "' file." << endl;
            system("pause");
            return false;
        }

        userXmlFile.SetData(newPassword);
        userXmlFile.OutOfElem();
        return userXmlFile.Save(getFileName());
    }

    cout << "No child node matching '" << getChildNodeName() << "' found. Please check structure of '" << getFileName() << "' file." << endl;
    return false;
}

vector <User> UserFile::loadUsersFromFile() {
    CMarkup userXmlFile;
    vector <User> users;

    if (!isFileExist())
        return users;

    if (loadXmlFile(userXmlFile) && enterXmlRootNode(userXmlFile)) {
        User user;
        const string userNodeName = getChildNodeName();

        while (userXmlFile.FindElem(userNodeName)) {
            userXmlFile.IntoElem();

            string idString = getElementData(userXmlFile, "id");
            user.firstName = getElementData(userXmlFile, "firstName");
            user.lastName = getElementData(userXmlFile, "lastName");
            user.userName = getElementData(userXmlFile, "login");
            user.userPassword = getElementData(userXmlFile, "password");

            userXmlFile.OutOfElem();

            if (idString.empty() || user.firstName.empty() || user.lastName.empty() || user.userName.empty() || user.userPassword.empty()) {
                cout << "Failed to load user data:" << endl << endl;
                cout << userXmlFile.GetSubDoc() << endl;
                cout << "Please check structure and content of '" << getFileName() << "' file." << endl;
                system("pause");
                exit(1);
            }

            user.id = stoi(idString);
            users.push_back(user);
        }

        if (!users.empty())
            setLastId(user.id);

    } else {
        exit(1);
    }

    return users;
}

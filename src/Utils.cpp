#include "Utils.h"

string Utils::readLine() {
    string input = "";

    getline(cin, input);
    return input;
}

bool Utils::validateInput(const string &input, FieldType type) {
    if (inputEmpty(input) || containsSpaces(input))
        return false;

    switch(type) {
        case(FieldType::FIRST_NAME): case(FieldType::LAST_NAME):
            return correctLength(input, 2, 20) && containsOnlyLetters(input);
        case(FieldType::LOGIN):
            return correctLength(input, 3, 20);
        case(FieldType::PASSWORD):
            return correctLength(input, 6, 20);
        default:
            cout << "Unknown field type." << endl;
            return false;
    }
}

bool Utils::inputEmpty(const string &input) {
    if (input.empty()) {
        cout << "Field cannot be empty." << endl;
        return true;
    }
    return false;
}

bool Utils::containsOnlyLetters(const string &input) {
    for (char character : input) {
        if (!isalpha(static_cast<unsigned char>(character))) {
            cout << "Field cannot contain '" << character << "' character." <<  endl;
            return false;
        }
    }
    return true;
}

//bool Utils::containsDigits(const string &input) {
//    for (char character : input) {
//        if (isdigit(static_cast<unsigned char>(character))) {
//            cout << "Field cannot contain digits." << endl;
//            return true;
//        }
//    }
//    return false;
//}

bool Utils::containsSpaces(const string &input) {
    for (char character : input) {
        if (character == ' ') {
            cout << "Field cannot contain spaces." << endl;
            return true;
        }
    }
    return false;
}

bool Utils::correctLength(const string &input, const int minLength, const int maxLength) {

    if (input.length() < size_t(minLength)) {
        cout << "Field is too short. Minimum length is " << minLength << " characters." << endl;
        return false;
    } else if (input.length() > size_t(maxLength)) {
        cout << "Field is too long. Maximum length is " << maxLength << " characters." << endl;
        return false;
    } else {
        return true;
    }
}

string Utils::upperFirstLowerRest(string &input) {
    input[0] = toupper(input[0]);
    transform(input.begin() + 1, input.end(), input.begin() + 1, ::tolower);
    return input;
}

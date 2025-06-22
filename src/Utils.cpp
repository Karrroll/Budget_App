#include "Utils.h"

char Utils::readCharacter() {
    char character = '\0';

    while (true) {
        string input = Utils::readLine();

        if (input.length() == 1) {
            character = input[0];
            break;
        }
        cout << "\nPlease enter a single character. Try again:\t";
    }
    return character;
}

string Utils::readLine() {
    string input = "";

    getline(cin, input);
    return input;
}

bool Utils::isValidAmount(const string &amount) {
    regex pattern(R"(^\d+([.,]\d{1,2})?$)");

    return regex_match(amount, pattern);
}

double Utils::parseAmount(const string &input) {
    string temp = input;
    replace(temp.begin(), temp.end(), ',', '.');

    double amount = stod(temp);

    return amount;
}

string Utils::formatAmount(const double &amount) {
    ostringstream oss;
    oss << fixed << setprecision(2) << amount;
    return oss.str();
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
        cout << "Field cannot be empty." << endl << endl;
        return true;
    }
    return false;
}

bool Utils::containsOnlyLetters(const string &input) {
    for (char character : input) {
        if (!isalpha(static_cast<unsigned char>(character))) {
            cout << "Field cannot contain '" << character << "' character." <<  endl << endl;
            return false;
        }
    }
    return true;
}

bool Utils::containsSpaces(const string &input) {
    for (char character : input) {
        if (character == ' ') {
            cout << "Field cannot contain spaces." << endl << endl;
            return true;
        }
    }
    return false;
}

bool Utils::correctLength(const string &input, const int minLength, const int maxLength) {

    if (input.length() < size_t(minLength)) {
        cout << "Field is too short. Minimum length is " << minLength << " characters." << endl << endl;
        return false;
    } else if (input.length() > size_t(maxLength)) {
        cout << "Field is too long. Maximum length is " << maxLength << " characters." << endl << endl;
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

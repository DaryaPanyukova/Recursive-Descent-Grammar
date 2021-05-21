#include <iostream>
#include <string>

std::string s;
int index = 0;

std::string GetWord();

std::string ErrorUnknownWord(std::string& word) {
    return (std::string) ("What is '" + word + "'");
}
std::string ErrorNotExpected(char symb) {
    if (symb == '\0')
        return "Space was not expecteed here";
    return symb + (std::string)" was not expected here";
}
std::string ErrorNotEnoughArguments() {
    return "Not enough arguments";
}
std::string ErrorTooManyArguments() {
    return "Too many arguments";
}
std::string ErrorSymbExpected(char symb) {
    return symb + (std::string)" expected";
}

std::string ReadOr() {
    bool result = false;
    int count = 0;
    if (s[index] != '(') {
        return ErrorSymbExpected('(');
    }
    for (;;) {
        ++index;
        std::string word = GetWord();
        if (word == "true" || word == "false") {
            count++;
            if (word == "true")
                result = true;
        } else {
            if (word == "What is ''") {
                return ErrorNotExpected(s[index]);
            }
            return word;
        }

        if (s[index] == ')') {
            ++index;
            if (count == 1) {
                return ErrorNotEnoughArguments();
            }

            if (result) {
                return "true";
            }
            else {
                return "false";
            }
        } else if (s[index] != ',') {
            return ErrorNotExpected(s[index]);
        }
    }
}

std::string ReadAnd() {
    bool result = true;
    int count = 0;
    if (index > s.size() || s[index] != '(')
        return ErrorSymbExpected('(');
    for (;;) {
        index++;
        std::string word = GetWord();
        if (word == "true" || word == "false") {
            count++;
            if (word == "false")
                result = false;
        }
        else {
            if (word == "What is ''") {
                return ErrorNotExpected(s[index]);
            }
            return word;
        }

        if (s[index] == ')') {
            index++;
            if (count == 1)
                return ErrorNotEnoughArguments();
            if (result)
                return "true";
            else
                return "false";
        }

        else if (s[index] != ',')
            return ErrorSymbExpected(')') + " or " + ErrorSymbExpected(',');
    }
}
std::string ReadNot() {
    int count = 0;
    if (s[index] != '(')
        return "error";
    bool result;
    std::string word;
    for (;;) {
        ++index;
        std::string word = GetWord();
        if (word == "true" || word == "false") {
            count++;
            if (word == "false") {
                result = true;
            } else {
                result = false;
            }
        }
        if (s[index] == ')') {
            index++;
            if (count == 1) {
                if (result)
                    return "true";
                else
                    return "false";
            }
        }
        else {
                return ErrorTooManyArguments();
            }
            return ErrorSymbExpected(')');
        
    }
}

std::string GetWord() {
    std::string word = "";
    while (s[index] >= 'a' && s[index] <= 'z') {
        word += s[index];
        index++;
    }

    if (word == "or")
        return ReadOr();
    else if (word == "and")
        return ReadAnd();
    else if (word == "not")
        return ReadNot();
    else if (word != "true" && word != "false")
        return ErrorUnknownWord(word);
    return word;
}

int main() {
    for (;;) {
        std::getline(std::cin, s);
        std::string res = GetWord();
        if (index != s.size() &&
            (res == "true" || res == "false"))
            res = ErrorNotExpected(s[index]);
        std::cout << res << '\n';
        index = 0;

    }
}

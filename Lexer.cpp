//
// Created by Rony Utevsky and Yehonatan Sofri on 12/21/19.
//

#include "Lexer.h"


/**
 * split the code into tokens
 */
void Lexer :: makeTokens(string filename) {
    string line;
    ifstream file(filename);

    //pattern = "(\{)|(\})|(var)\s|(connectControlClient)\((.+)\s*,\s*(\d{1,5})\)|(\w+)\s*(=)\s*(.+)|([Ww]hile|[Ii]f)\s*(.+)\s*(<=|>=|<|>|==|!=)\s*(.+)(\{)|(\w+)\s*(->|<-)|([\w\_]+)\s*\((var\s)?(.+)\)";

    string pattern;
    // match opening and closing brackets
    pattern = "({)|(})|";
    // match the word var
    pattern += "(var)\\s|";
    // match connectControlClient function and its params
    pattern += "(connectControlClient)\\((.+)\\s*,\\s*(\\d{1,5})\\)|";
    // match var assignment of the pattern `X = Y`
    pattern += "(\\w+)\\s*(=)\\s*(.+)|";
    // match while and if
    pattern += "([Ww]hile|[Ii]f)\\s*(.+)\\s*(<=|>=|<|>|==|!=)\\s*(.+)(\\{)|";
    // match simulator variable binding
    pattern += "(\\w+)\\s*(->|<-)|";
    // match function name + function params
    pattern += "([\\w\\_]+)\\s*\\((var\\s)?(.+)\\)";

    while (getline(file, line)) {
        auto matches = doRegex(line, pattern);

        // check if the matches are legal tokens
        for (string& match: matches) {
            if (!isLegalToken(match)) {
                cerr << "Error: illegal token:" << match << endl;
            }
        }

        // append the new tokens to the general tokens vector
        tokens.insert(tokens.end(), matches.begin(), matches.end());
        // add a `new line` token
        tokens.emplace_back("\n");
    }
}

/**
 * Check if the token is legal
 * @param token the token
 * @return true if legal token
 */
bool Lexer :: isLegalToken(string token) {
    int i = 0;
    bool isString = false;
    if (token[0] == '"') {
        isString = true;
    }


    for (char c : token) {
        // if it's a string and if the string is terminated with `"` or if the last char is not `"`
        if (isString && ((c == '"' && i > 0 && i != token.size() - 1) || (i != token.size() -1 && c != '"'))) {
            return false;
        }
        else if (isSkippableChar(c)) {
            return false;
        }
        i++;
    }
    return true;
}

/**
 * check if the char is skippable
 * @param c the char
 * @return true if skippable
 */
bool Lexer :: isSkippableChar(char c) {
    return c == ' ' || c == ',' || c == '\r' || c == '\t' || c == '(' || c == ')';
}

/**
 * Check if the current line is a variable assignment, i.e. if we detect `var = ...`
 * @return
 */
bool Lexer :: isVarAssignment() {
    auto it = tokens.end() - 1;
    return *it == "=" && isLegalVar(*(it-1));
}

/**
 * Check if a string is a legal variable name
 * @param var the string to check
 * @return true if the string is a legal variable name
 */
bool Lexer :: isLegalVar(string &var) {
    int i = 0;
    for (char c : var) {
        if (i == 0 && !isLetter(c) && c != '_') {
            return false;
        } else if (!isDigit(c) && !isLetter(c) && c != '_') {
            return false;
        }

        i++;
    }
    return true;
}


/**
 * Check if a string is a legal function name
 * @param var the string to check
 * @return true if the string is a legal function name
 */
bool Lexer :: isLegalFunc(string &func) {
    return isLegalVar(func);
}

/**
 * check if a char is a letter
 * @param c the char
 * @return true if the char is a letter
 */
bool Lexer :: isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * check if a char is a digit
 * @param c the char
 * @return true if the char is a digit
 */
bool Lexer :: isDigit(char c) {
    return c >= '0' && c <= '9';
}

/**
 * get matches from string using regex
 * @param str a single line
 * @param pattern the pattern
 * @return a vector of matches
 */
vector<string> Lexer :: doRegex(string str, string pattern) {
    vector<string> matches;

    auto reg = regex(pattern);
    auto iter = sregex_iterator(str.begin(), str.end(), reg);
    auto iterHelper = sregex_iterator();

    // loop the matches
    for (auto i = iter; i != iterHelper; ++i) {
        int times = 0;
        string lastMatch;
        for (string match : *i) {
            // skip empty matches
            if (match.empty()) {
                continue;
            }

            // retrieve only the unique matches in each match group
            if (match != lastMatch) {
                matches.push_back(match);
                times++;
            }
            lastMatch = match;
        }
    }

    return matches;
}

/**
 * find the closing bracket of the scope
 * @param start the index to start looking from
 * @return the index of the closing bracket
 */
int Lexer :: findClosingBracketIndex(int start) {
    int countOpening = 0, countClosing = 0;
    for (int i = start; i < tokens.size(); ++i) {
        if (tokens[i] == "{") {
            countOpening++;
        } else if (tokens[i] == "}") {
            countClosing++;
        }

        if (countOpening == countClosing) {
            return start + i;
        }
    }

    throw "Error: Cannot find brackets";
};

/**
 * removes wrapping quotes from string
 * @param string
 * @return the string without the wrapping quotes
 */
string Lexer :: removeQuotes(string str) {
    if (str[0] == '"' && str[str.size()] == '"') {
        // remove first "
        str = str.substr(1);
        // remove last "
        str.pop_back();
    }
}
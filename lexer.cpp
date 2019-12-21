//
// Created by Rony Utevsky and Yehonatan Sofri on 12/21/19.
//

#include "GeneralData.h"
#include "lexer.h"

/**
 * constrcuctor
 */
Lexer :: Lexer() {}

/**
 * constrcuctor
 * @param filename file's name
 */
Lexer :: Lexer(string &filename): filename(filename) {}

/**
 * split the code into tokens
 */
void Lexer :: makeTokens() {
    string line;
    bool readingString = false;
    ifstream file(this -> filename);

    while (getline(file, line)) {
        string token;

        for (char c : line) {
            // check if finished reading a token
            if (isSkippableChar(c) && !readingString && !isVarAssignment()) {

                // only approve legal tokens
                if (isLegalToken(token)) {
                    tokens.push_back(token);
                    token = "";
                }

                if (c == '\n') {
                    tokens.emplace_back("\n");
                    token = "";
                }
            }
                // if the current line is a variable assignment that looks like `var = ...`, then we will treat the
                // whole expression after the `=` as a single token that will be parsed afterwards
            else if (isVarAssignment()) {
                if (c == '\n') {
                    tokens.push_back(token);
                    tokens.emplace_back("\n");
                    token = "";
                } else {
                    token += c;
                }

            } else {
                if (c == '"'){
                    if (readingString) {
                        tokens.push_back(token);
                        token = "";
                    }
                    readingString = !readingString;
                } else {
                    token += c;
                }
            }
        }
    }
}

/**
 * Check if the token is legal
 * @param token the token
 */
bool Lexer :: isLegalToken(string token) {
    for (char c : token) {
        if (isSkippableChar(c)) {
            return false;
        }
    }
    return true;
}

/**
 * check if the char is skippable
 * @param c the char
 * @return true if skippable
 */
bool Lexer :: isSkippableChar(char c) {
    return c == ' ' || c == ',' || c == '\n' || c == '\r' || c == '\t' || c == '(' || c == ')';
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

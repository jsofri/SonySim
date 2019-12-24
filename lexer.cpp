//
// Created by Rony Utevsky and Yehonatan Sofri on 12/21/19.
//
// var Print Sleep while
// can print vars!!! @@@@@@@@@@@@@@@@@@@
//
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
    ifstream file(this -> filename);
    string pattern = R"lit((\{)|(\})|(var)\s|(connectControlClient)\("([\S]*)",(\d{1,5})\)|(\w+)\s*(=)\s*(.+)|([Ww]hile|[Ii]f)\s*(.+)\s*(<=|>=|<|>|==|!=)\s*(.+)(\{)|(\w+)\s*(->|<-)\s*(sim)\((.+)\)|([\w\_]+)\s*\((var\s)?(.+)\))lit";

    while (getline(file, line)) {
        auto matches = doRegex(line, pattern);
        tokens.insert(tokens.end(), matches.begin(), matches.end());
        tokens.emplace_back("\n");
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
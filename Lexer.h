//
// Created by Rony Utevsky and Yehonatan Sofri on 12/19/19.
//

#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

class Lexer {
    public:

    /**
     * split the code into tokens
     */
    static void makeTokens(string);

    /**
     * Check if the token is legal
     * @param token the token
     */
    static bool isLegalToken(string token);

     /**
      * check if the char is skippable
      * @param c the char
      * @return true if skippable
      */
     static bool isSkippableChar(char c);

     /**
      * Check if the current line is a variable assignment, i.e. if we detect `var = ...`
      * @return
      */
     static bool isVarAssignment();

     /**
      * Check if a string is a legal variable name
      * @param var the string to check
      * @return true if the string is a legal variable name
      */
     static bool isLegalVar(string &var);


    /**
     * Check if a string is a legal function name
     * @param var the string to check
     * @return true if the string is a legal function name
     */
    static bool isLegalFunc(string &func);

     /**
      * check if a char is a letter
      * @param c the char
      * @return true if the char is a letter
      */
     static bool isLetter(char c);

    /**
     * check if a char is a digit
     * @param c the char
     * @return true if the char is a digit
     */
    static bool isDigit(char c);

    /**
     * get matches from string using regex
     * @param str a single line
     * @param pattern the pattern
     * @return a vector of matches
     */
    static vector<string> doRegex(string, string);

    /**
     * find the closing bracket of the scope
     * @param start the index to start looking from
     * @return the index of the closing bracket
     */
    static int findClosingBracketIndex(int);

    /**
     * removes wrapping char from string
     * @param string the text
     * @param char the char to trim
     * @return the string without the wrapping char
     */
    static string trim(string, char);

    /**
     * trim spaces
     * @param str the text
     * @return the text without leading and trailing spaces
     */
    static string trim(string);
};

#endif //LEXER_H

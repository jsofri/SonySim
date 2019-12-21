//
// Created by rony on 12/19/19.
//

#ifndef LEXER_H
#define LEXER_H

class Lexer {
    string filename;

    public:

    /**
     * constrcuctor
     * @param filename file's name
     */
    explicit Lexer(string &filename);

    /**
     * split the code into tokens
     */
    void makeTokens();

    /**
     * Check if the token is legal
     * @param token the token
     */
     bool isLegalToken(string token);

     /**
      * check if the char is skippable
      * @param c the char
      * @return true if skippable
      */
     bool isSkippableChar(char c);

     /**
      * Check if the current line is a variable assignment, i.e. if we detect `var = ...`
      * @return
      */
     bool isVarAssignment();

     /**
      * Check if a string is a legal variable name
      * @param var the string to check
      * @return true if the string is a legal variable name
      */
     bool isLegalVar(string &var);


    /**
     * Check if a string is a legal function name
     * @param var the string to check
     * @return true if the string is a legal function name
     */
    bool isLegalFunc(string &func);

     /**
      * check if a char is a letter
      * @param c the char
      * @return true if the char is a letter
      */
     bool isLetter(char c);

    /**
     * check if a char is a digit
     * @param c the char
     * @return true if the char is a digit
     */
    bool isDigit(char c);

    /**
    * destructor
    */
    ~Lexer() = default;
};

#endif //LEXER_H

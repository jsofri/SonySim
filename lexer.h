//
// Created by rony on 12/19/19.
//

#ifndef LEXER_H
#define LEXER_H

using namespace std;

class Lexer {
    string filename;
    vector<string> tokens;

    public:
    /**
     * constrcutor
     * @param filename file's name
     */
    Lexer(string &filename): filename(filename) {}

    /**
     * split the code into tokens
     */
    void makeTokens() {
        string line;
        bool readingString = false;
        ifstream file(this -> filename);

        while (getline(file, line)) {
            string token = "";

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
     * returns the token array
     * @return the token array
     */
    vector<string> getTokens(){
        return this -> tokens;
    }

    /**
     * Check if the token is legal
     * @param token the token
     */
     bool isLegalToken(string token) {
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
     bool isSkippableChar(char c) {
         return c == ' ' || c == ',' || c == '\n' || c == '\r' || c == '\t' || c == '(' || c == ')';
     }

     /**
      * Check if the current line is a variable assignment, i.e. if we detect `var = ...`
      * @return
      */
     bool isVarAssignment() {
         vector<string>::iterator it = tokens.end() - 1;
         return *it == "=" && isLegalVar(*(it-1));
     }

     /**
      * Check if a string is a legal variable name
      * @param var the string to check
      * @return true if the string is a legal variable name
      */
     bool isLegalVar(string var) {
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
    bool isLegalFunc(string func) {
        return isLegalVar(func);
    }

     /**
      * check if a char is a letter
      * @param c the char
      * @return true if the char is a letter
      */
     bool isLetter(char c) {
         return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
     }

    /**
     * check if a char is a digit
     * @param c the char
     * @return true if the char is a digit
     */
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    /**
    * destructor
    */
    ~Lexer() = default;
};

#endif //LEXER_H

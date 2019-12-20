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
        ifstream file(this -> filename);

        while(getline(file, line)) {
            string token = "";

            for (char c : line) {
                // finished reading a token?
                // @@ strings are without quotes @@@@@
                if (isSkippableChar(c) || readingString) {

                    // only approve legal tokens
                    if (isLegalToken(token)) {
                        tokens.push_back(token);
                        token = "";
                    }

                    if (c == '\n') {
                        tokens.emplace_back("\n");
                        break;
                    }
                } else {
                    if (c == '"'){
                        if (!readingString) {
                            
                        } else {

                        }
                        readingString = !readingString;
                    }
                    token += c;
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
    * destructor
    */
    ~Lexer() = default;
};

#endif //LEXER_H

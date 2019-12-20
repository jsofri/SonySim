//
// Created by rony on 12/19/19.
//

#ifndef PARSER_H
#define PARSER_H

class Parser {
    vector<string> tokens;
    map<string, Command> cmdMap;

    public:
    /**
     * Constructor
     */
     Parser(vector<string> &tokens): tokens(tokens) {}


    /**
     * Parse the tokens
     */
    void parse() {
        int index = 0;
        vector<string> tokensRow;

        while (index < tokens.size()) {6
            if (tokens[index] == "\n") {
                string cmdType = parseCommandType(tokensRow);
            } else {
                tokensRow.push_back(tokens[index]);
            }

            index++;
        }

        if (isWhile(tokensRow)) {

        } else if (isIf(tokensRow)) {

        } else if (isFunctionDef(tokensRow)) {
            Commandfunc();
            cmdMap[] =

        } else if (isFunctionUse(tokensRow)){

        } else if(isAssignment(tokensRow)) {

        } else if (isStream(tokensRow)) {

        }
    }

};

#endif //PARSER_H

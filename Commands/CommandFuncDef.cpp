//
// Created by rony on 12/26/19.
//

#include "CommandFuncDef.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandFuncDef :: execute(int index) {
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (tokens[index] == "\n") {
        return execute(index + 1);
    }

    string func = tokens[index];
    auto params = funcMap[func].second;

    // look for param names
    while (tokens[index] != "\n") {
        if (tokens[index] != "var") {
            string param = tokens[index];

            // check if iilegal var name
            if (!Lexer::isLegalVar(param)) {
                throw "Error: Illegal parameter name in function";
            }

            // push parameter
            params.push_back(param);
        }
    }

    // find the index of the end of the function's definition
    int closingBracket = Lexer::findClosingBracketIndex(index);
    return closingBracket;
}
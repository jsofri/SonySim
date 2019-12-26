//
// Created by rony on 12/26/19.
//

#include "../GeneralData.h"
#include "CommandPrint.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandPrint :: execute(int index) {
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (tokens[index] == "\n") {
        return execute(index + 1);
    }

    string print = tokens[++index];
    string value = print;

    // check if it's a variable
    if (Lexer::isLegalVar(print)) {
        if (!symbol_table.exists(print)) {
            throw "Error: unknown variable passed to Print";
        }
        value = symbol_table.get(print).value;
    } else {
        // remove leading and trailing quotes
        value = Lexer::removeQuotes(value);
    }

    // print the value
    cout << value << endl;

    return index + 2;
}
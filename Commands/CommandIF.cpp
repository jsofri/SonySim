//
// Created by rony on 12/26/19.
//

#include "CommandIF.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandIF :: execute(int index) {
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (tokens[index] == "\n") {
        return execute(index + 1);
    }

    ConditionFactory factory;
    Condition* cond = factory.setCondition(tokens[++index], tokens[++index], tokens[++index]);

    int closingBracket = Lexer::findClosingBracketIndex(index);

    if (cond -> isTrue()) {
        // create new symbol table for the new scope
        symbol_table.newTable();

        // parse the function
        Parser parser;
        parser.parse(index + 1, closingBracket);

        symbol_table.deleteTable();
    }

    return closingBracket + 2;
}
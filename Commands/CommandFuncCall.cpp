//
// Created by rony on 12/26/19.
//

#include "CommandFuncCall.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandFuncCall :: execute(int index) {
    auto it = tokens.begin() + index;

    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (*it == "\n") {
        return execute(index + 1);
    }

    string func = *it;

    // get start and end indexes of the function scope
    auto func_start_index = funcMap[func].first.first;
    auto func_end_index = funcMap[func].first.second;

    // get the param values
    auto params = funcMap[func].second;
    vector<string> values;

    for (; it !=  tokens.end(); ++it) {
        if (*it == "\n") {
            break;
        }
        string value = *it;
        values.push_back(value);
        index++;
    }

    // make map of param names and values
    unordered_map<string, string> paramMap;
    int i;
    for (i = 0; i < params.size(); ++i) {
        auto param = params.begin() + i;
        auto value = values.begin() + i;
        paramMap[*param] = *value;
    }

    // make new inner symbol table
    symbol_table.newTable(paramMap);

    // parse the function
    Parser parser;
    parser.parse(func_start_index, func_end_index);

    // remove the innermost symbol table as the current scope is over
    symbol_table.deleteTable();

    return index;
}
//
// Created by Rony Utevsky and Yehonatan Sofri on 12/21/19.
//

#include "GeneralData.h"
#include "lexer.h"
#include "parser.h"


/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandPrint :: execute(int index) {
    auto it = tokens.begin();

    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (*it == "\n") {
        return execute(index + 1);
    }

    cout << *(it + index + 1) << endl;
    return index + 1;
}


/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandFuncDef :: execute(int index) {
    auto it = tokens.begin() + index;

    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (*it == "\n") {
        return execute(index + 1);
    }

    Lexer lexer;
    string func = *it;
    auto params = funcMap[func].second;

    // look for param names
    for (; it != tokens.end(); ++it) {
        if (*it == "\n") {
            break;
        }

        if (*it != "var") {
            string param = *it;
            if (lexer.isLegalVar(param)) {
                params.push_back(param);
            } else {
                throw "Error: Illegal parameter name in function";
            }
        }
    }

    // find the final index of the function definition
    for (; it != tokens.end(); ++it) {
        // Note: if there's is another scope inside the function, this code won't work - we'll have to count `{` and `}`
        if (*it == "}") {
            funcMap[func].first.second = index;
            // remove the innermost symbol table as the current scope is over 
            symbol_table.deleteTable();
            return index + 1;
        }
        index++;
    }

    throw "Error: closing bracket not found for function";
}


/**
 * Interpret and execute.
 * Summary: It makes a subvector of the token vector and replaces all parameter names with the values which are passed
 * to the function.
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

    // make a new subvector
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

    return index;
}
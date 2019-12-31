/**
 * this class is for executing a function.
 * notice that there's CommandFuncDef for setting a function.
 *
 * @date 12/26/19
 * @author Rony 
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "CommandFuncCall.h"
#include "../FloatFromString.h"
#include "../Lexer.h"
#include "../Parser.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandFuncCall :: execute(int index) {

    string func = tokens[index];

    // get the param values
    vector<string> values;

    while (tokens[++index] != "\n") {
        string value = tokens[index];
        values.push_back(value);
    }

    // make map of param names and values
    auto & params = funcMap[func].second;
    unordered_map<string, VarData> paramMap;

    for (int i = 0; i < params.size(); ++i) {
        auto param = params[i];
        auto value = values[i];
        paramMap[param] = VarData(FloatFromString::calculateString(value));
    }

    // make new inner symbol table
    symbol_table.newTable(paramMap);

    // get start and end indexes of the function scope
    int func_start_index = funcMap[func].first;
    int func_end_index = Lexer::findClosingBracketIndex(func_start_index);

    // parse the function
    Parser parser;
    parser.parse(func_start_index, func_end_index);

    // remove the innermost symbol table as the current scope is over
    symbol_table.deleteTable();

    return index + 1;
}

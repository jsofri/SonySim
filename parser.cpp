//
// Created by rony on 12/21/19.
//

#include "GeneralData.h"
#include "parser.h"
#include "lexer.h"
#include "Command.h"

/**
 * Parse the tokens and execute commands
 * @param start the index to begin parsing
 */
void Parser :: parse(int start) {
    int end;
    vector<string> tokensRow;

    while (start < tokens.size()) {
        if (tokens[start] == "\n") {
            string cmdType;
            // try to parse the row
            try {
                cmdType = parseCommandType(tokensRow, start);
            } catch (char* exception) {
                cerr << exception;
            }

            // try to execute the command
            Command c = cmdMap[cmdType];
            try {
                end = c.execute(index);
                start = end;
            } catch (char* exception) {
                cerr << exception;
            }

        } else {
            tokensRow.push_back(tokens[start]);
            start++;
        }
    }
}

/**
 * Parse the tokens and execute commands.
 * Default index is 0.
 */
void Parser :: parse() {
    int start = 0;
    parse(start);
}

/**
 * parse the command type (var, update, func, while, if etc.)
 * @param tokensRow a row of tokens
 * @return the command type
 */
string Parser :: parseCommandType(vector<string> &row, int index) {
    string type;
    if (isWhile(row)) {
        type = COM_WHILE;
    } else if (isIF(row)) {
        type = COM_IF;
    } else if (isUpdate(row)) {
        type = COM_UPDATE;
    } else if (isPrint(row)) {
        type = COM_PRINT;
    } else if (isSleep(row)) {
        type = COM_SLEEP;
    } else if (isOpenServer(row)) {
        type = COM_OPEN_SERVER;
    } else if (isConnect(row)) {
        type = COM_CONNECT;
    } else if (isVar(row)) {
        type = COM_VAR;
    } else if (isFuncDef(row, index)) {
        type = COM_FUNC_DEF;
    } else if (isFuncCall(row)) {
        type = COM_FUNC_CALL;
    } else {
        throw "Error: unknown command.";
    }

    return COM_WHILE;
}

/**
 * Check if a while loop should run
 * @param row the token row
 * @return true if a while loop should run
 */
bool Parser :: isWhile(vector<string> &row) {
    auto it = row.begin();
    string token = *it;
    return token == "while";
}

/**
* Check if an IF condition should run
* @param row the token row
* @return true if an IF condition should run
*/
bool Parser :: isIF(vector<string> &row) {
    auto it = row.begin();
    string token = *it;
    return token == "if";
}

/**
* Check if a Print command should run
* @param row the token row
* @return true if a Print command should run
*/
bool Parser :: isPrint(vector<string> &row) {
    auto it = row.begin();
    string token = *it;
    return token == "Print";
}

/**
* Check if a Sleep command should run
* @param row the token row
* @return true if a Sleep command should run
*/
bool Parser :: isSleep(vector<string> &row) {
    auto it = row.begin();
    string token = *it;
    return token == "Sleep";
}

/**
* Check if an `Open Data Server` command should run
* @param row the token row
* @return true if an `Open Data Server` command should run
*/
bool Parser :: isOpenServer(vector<string> &row) {
    auto it = row.begin();
    string token = *it;
    return token == "openDataServer";
}

/**
* Check if a `Connect Control Client` command should run
* @param row the token row
* @return true if a `Connect Control Client` command should run
*/
bool Parser :: isConnect(vector<string> &row) {
    auto it = row.begin();
    string token = *it;
    return token == "connectControlClient";
}

/**
 * Check if a variable command should run
 * @param row the token row
 * @return true if a variable command should run
 */
bool Parser :: isVar(vector<string> &row) {
    string dummy;
    Lexer lexer(dummy);

    auto it = row.begin();
    // match e.g. `var heading = ...`
    if (*it == "var" && lexer.isLegalVar(*(it+1)) && *(it+2) == "=") {
        return true;
    }
        // match e.g. `heading = ...`
    else if (lexer.isLegalVar(*it) && *(it+1) == "=") {
        return true;
    }

    return false;
}

/**
 * Check if a function definition command should run
 * @param row the token row
 * @return true if a function definition command should run
 */
bool Parser :: isFuncDef(vector<string> &row, int index) {
    string dummy;
    Lexer lexer(dummy);
    string func = *row.begin();
    if (lexer.isLegalFunc(func) && *(row.end() - 1) == "{") {
        funcMap[func].first = index;
        return true;
    }

    return false;
}

/**
 * Check if a function call command should run
 * @param row the token row
 * @return true if a function call command should run
 */
bool Parser :: isFuncCall(vector<string> &row) {
    string dummy;
    Lexer lexer(dummy);
    string func = *row.begin();
    // check if the function name is legal AND if it exists in the funcMap (i.e. if it was defined before)
    return lexer.isLegalFunc(func) && funcMap.count(func);
}

/**
* Check if an Update command should run
* @param row the token row
* @return true if an Update command should run
*/
bool Parser :: isUpdate(vector<string> &row) {
    bool arrowExists = false, simExists = false;
    vector<string>::iterator it;

    for (it = row.begin(); it != row.end(); ++it) {
        // if the row has both an arrow and a `sim` function
        if (arrowExists && simExists) {
            return true;
        }

        string token = *it;
        if (token == "->" || token == "<-") {
            arrowExists = true;
        } else if (token == "sim") {
            simExists = true;
        }
    }

    return false;
}
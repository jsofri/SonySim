//
// Created by Rony Utevsky and Yehonatan Sofri on 12/21/19.
//

#include "GeneralData.h"
#include "GlobalVars.h"
#include "Commands/Command.h"
#include "Parser.h"
#include "Lexer.h"

/**
 * Parse the tokens and execute commands
 * @param start the index to begin parsing
 * @param tokenArr the vector to use
 */
void Parser :: parse(int start, int end, vector<string> &tokenArr) {
    vector<string> tokensRow;

    int startOfCommand = start;
    while (start < end) {
        if (tokenArr[start] == "\n" && tokensRow.size() > 0) {
            string cmdType;
            // try to parse the row
            try {
                cmdType = parseCommandType(tokensRow, start);
            } catch (char* exception) {
                cerr << exception << endl;
            }

            // try to execute the command
            Command* c = cmdMap[cmdType];
            try {
                start = c -> execute(startOfCommand);
                startOfCommand = start;
            } catch (char* exception) {
                cerr << exception << endl;
            }

            // clear row
            tokensRow.clear();

        } else {
            tokensRow.push_back(tokens[start]);
            start++;
        }
    }
}

/**
 * Parse the tokens and execute commands.
 */
void Parser :: parse() {
    int start = 0;
    int end = (int) tokens.size();
    parse(start, end, tokens);
}

/**
 * Parse the tokens and execute commands.
 * @param tokenArr token array
 */
void Parser :: parse(vector<string> tokenArr) {
    int start = 0;
    int end = (int) tokens.size();
    parse(start, end, tokenArr);
}

/**
 * Parse the tokens and execute commands.
 * @param start the index to begin parsing
 */
void Parser :: parse(int start) {
    int end = (int) tokens.size();
    parse(start, end, tokens);
}

/**
 * Parse the tokens and execute commands.
 * @param start the index to begin parsing
 * @param end the index to end parsing
 */
void Parser :: parse(int start, int end) {
    parse(start, end, tokens);
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
    } else if (isPrint(row)) {
        type = COM_PRINT;
    } else if (isSleep(row)) {
        type = COM_SLEEP;
    } else if (isOpenServer(row)) {
        type = COM_SERVER;
    } else if (isConnect(row)) {
        type = COM_CLIENT;
    } else if (isVar(row) || isUpdate(row)) {
        type = COM_VAR;
    } else if (isFuncDef(row, index)) {
        type = COM_FUNC_DEF;
    } else if (isFuncCall(row)) {
        type = COM_FUNC_CALL;
    } else if (isComment(row)) {
        type = COM_COMMENT;
    }  else {
        throw "Error: unknown command.";
    }

    return type;
}

/**
 * Check if a while loop should run
 * @param row the token row
 * @return true if a while loop should run
 */
bool Parser :: isWhile(vector<string> &row) {
    return row[0] == "while";
}

/**
* Check if an IF condition should run
* @param row the token row
* @return true if an IF condition should run
*/
bool Parser :: isIF(vector<string> &row) {
    return row[0] == "if";
}

/**
* Check if a Print command should run
* @param row the token row
* @return true if a Print command should run
*/
bool Parser :: isPrint(vector<string> &row) {
    return row[0] == "Print";
}

/**
* Check if a Sleep command should run
* @param row the token row
* @return true if a Sleep command should run
*/
bool Parser :: isSleep(vector<string> &row) {
    return row[0] == "Sleep";
}

/**
* Check if an `Open Data Server` command should run
* @param row the token row
* @return true if an `Open Data Server` command should run
*/
bool Parser :: isOpenServer(vector<string> &row) {
    return row[0] == "openDataServer";
}

/**
* Check if a `Connect Control Client` command should run
* @param row the token row
* @return true if a `Connect Control Client` command should run
*/
bool Parser :: isConnect(vector<string> &row) {
    return row[0] == "connectControlClient";
}

/**
* Check if a the line is commented and should be ingored
* @param row the token row
* @return true if the line is a comment and should be ingored
*/
bool Parser :: isComment(vector<string> &row) {
    return row[0][0] == '/' || row[0][0] == '#';
}

/**
 * Check if a variable command should run
 * @param row the token row
 * @return true if a variable command should run
 */
bool Parser :: isVar(vector<string> &row) {
    // match e.g. `var heading = ...`
    if (row[0] == "var" && Lexer::isLegalVar(row[1]) && row[2] == "=") {
        return true;
    }
    // match e.g. `heading = ...`
    else if (Lexer::isLegalVar(row[0]) && row[1] == "=") {
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
    string func = row[0];
    if (Lexer::isLegalFunc(func) && *(row.end() - 1) == "{") {
        funcMap[func].first = index + 1;
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
    string func = row[0];
    // check if the function name is legal AND if it exists in the funcMap (i.e. if it was defined before)
    return Lexer::isLegalFunc(func) && funcMap.count(func);
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
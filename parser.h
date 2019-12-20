//
// Created by rony on 12/19/19.
//

#ifndef PARSER_H
#define PARSER_H

#define COM_VAR "var"
#define COM_WHILE "while"
#define COM_IF "if"
#define COM_FUNC_DEF "funcDef"
#define COM_FUNC_CALL "funcCall"
#define COM_UPDATE "update"
#define COM_PRINT "print"
#define COM_SLEEP "sleep"
#define COM_OPEN_SERVER "openServer"
#define COM_CONNECT "connect"

class Parser {
    vector<string> tokens;
    unordered_map<string, Command> cmdMap;
    // map that stores function names and their index of definition in the lexer array
    unordered_map<string, int> funcMap;

    public:
    /**
     * Constructor
     */
     Parser(vector<string> &tokens): tokens(tokens) {
         // init the commands in the command map
         cmdMap[COM_VAR] = new CommandVar();
         cmdMap[COM_WHILE] = new CommandWhile();
         cmdMap[COM_IF] = new CommandIF();
         cmdMap[COM_FUNC_DEF] = new CommandFuncDef();
         cmdMap[COM_FUNC_CALL] = new CommandFuncCall();
         cmdMap[COM_UPDATE] = new CommandUpdate();
         cmdMap[COM_PRINT] = new CommandPrint();
         cmdMap[COM_SLEEP] = new CommandSleep();
         cmdMap[COM_OPEN_SERVER] = new CommandOpenServer();
         cmdMap[COM_CONNECT] = new CommandConnect();
     }


    /**
     * Parse the tokens and execute commands
     */
    void parse() {
        int start = 0, end;
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
                    end = c.execute(index, tokens);
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
     * parse the command type (var, update, func, while, if etc.)
     * @param tokensRow a row of tokens
     * @return the command type
     */
    string parseCommandType(vector<string> &row, int index) {
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
    bool isWhile(vector<string> &row) {
        auto it = row.begin();
        string token = *it;
        return token == "while";
    }

    /**
    * Check if an IF condition should run
    * @param row the token row
    * @return true if an IF condition should run
    */
    bool isIF(vector<string> &row) {
        auto it = row.begin();
        string token = *it;
        return token == "if";
    }

    /**
    * Check if a Print command should run
    * @param row the token row
    * @return true if a Print command should run
    */
    bool isPrint(vector<string> &row) {
        auto it = row.begin();
        string token = *it;
        return token == "Print";
    }

    /**
    * Check if a Sleep command should run
    * @param row the token row
    * @return true if a Sleep command should run
    */
    bool isSleep(vector<string> &row) {
        auto it = row.begin();
        string token = *it;
        return token == "Sleep";
    }

    /**
    * Check if an `Open Data Server` command should run
    * @param row the token row
    * @return true if an `Open Data Server` command should run
    */
    bool isOpenServer(vector<string> &row) {
        auto it = row.begin();
        string token = *it;
        return token == "openDataServer";
    }

    /**
    * Check if a `Connect Control Client` command should run
    * @param row the token row
    * @return true if a `Connect Control Client` command should run
    */
    bool isConnect(vector<string> &row) {
        auto it = row.begin();
        string token = *it;
        return token == "connectControlClient";
    }

    /**
     * Check if a variable command should run
     * @param row the token row
     * @return true if a variable command should run
     */
    bool isVar(vector<string> &row) {
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
    bool isFuncDef(vector<string> &row, int index) {
        string dummy;
        Lexer lexer(dummy);
        string func = *row.begin();
        if (lexer.isLegalFunc(func) && *(row.end() - 1) == "{") {
            funcMap[func] = index;
            return true;
        }

        return false;
    }

    /**
     * Check if a function call command should run
     * @param row the token row
     * @return true if a function call command should run
     */
    bool isFuncCall(vector<string> &row, int index) {
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
    bool isUpdate(vector<string> &row) {
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

};

#endif //PARSER_H

/**
 * Abstract class for all command objects.
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef COMMAND_H
#define COMMAND_H


// Parser forward declaration

#include "GeneralData.h"
#include "parser.h"

using namespace std;

/**
 * Base abstract class of Command object
 */
class Command {
    protected:
    //count number of strings that were handled in the vector
    int indexCounter = 0;

    public:
    /**
     * interpret and execute, depending on the strings sequence in the vector.
     *
     * @param vector<string> & the tokens from lexer
     * @param int index - index in the vector
     * @return int - index counter in the vector
     */
    virtual int execute(int) = 0;
};

/**
 * Print Command
 */
class CommandPrint: Command {

    int execute(int index) {
        auto it = tokens.begin();
        // if it's a new line string (maybe a leftover from the last command), then move on to the next token
        if (*it == "\n") {
            index++;
        }

        cout << *(it + index + 1) << endl;
        return index + 1;
    }
};


/**
 * Function Definition Command
 */
class CommandFuncDef: Command {
    int execute(int index) {
        Parser parser;
        parser.parse(index);
    }

};

/**
 * cmdMap: Global var
 * Initialize the commands in the command map
 *
 * Note: I had to put it here in Command.h and not in GeneralData.h, and if I did, it would not compile
 *       becuase GeneralData would have to include Command.h in order to initialize this map values, and the problem
 *       is that also Command.h includes GeneralData.h and thus creating a inter-dependency.
 */
extern unordered_map<string, Command> cmdMap = {{COM_VAR, new CommandVar()},
                                                {COM_WHILE, new CommandWhile()},
                                                {COM_IF, new CommandIF()},
                                                {COM_FUNC_DEF, new CommandFuncDef()},
                                                {COM_FUNC_CALL, new CommandFuncCall()},
                                                {COM_UPDATE, new CommandUpdate()},
                                                {COM_PRINT, new CommandPrint()},
                                                {COM_SLEEP, new CommandSleep()},
                                                {COM_OPEN_SERVER, new CommandOpenServer()},
                                                {COM_CONNECT, new CommandConnect()}};



#endif //COMMAND_H

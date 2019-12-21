/**
 * Abstract class for all command objects.
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef COMMAND_H
#define COMMAND_H

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
    virtual int execute(int, vector<string> &) = 0;
};

/**
 * Print Command
 */
class CommandPrint: protected Command {

    int execute(int index, vector<string> &tokens) {
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
class CommandFuncDef: protected Command {
   // working on this...
};



#endif //COMMAND_H

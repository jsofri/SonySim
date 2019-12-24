/**
 * Abstract class for all command objects.
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef COMMAND_H
#define COMMAND_H

/**
 * Base abstract class of Command object
 */
class Command {
    protected:
    //count number of strings that were handled in the vector
    int indexCounter = 0;

    public:
    /**
     * interpret and execute
     *
     * @param index index in the vector
     * @return new index counter in the vector that will be passed to the next command
     */
    virtual int execute(int) = 0;
};

/**
 * Print Command
 */
class CommandPrint: Command {
    int execute(int index);
};


/**
 * Function Definition Command
 */
class CommandFuncDef: Command {
    int execute(int index);
};

/**
 * Function Call Command
 */
class CommandFuncCall: Command {
    int execute(int index);
};

#endif //COMMAND_H

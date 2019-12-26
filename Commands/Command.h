/**
 * Abstract class for all command objects.
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "CommandFuncCall.h"
#include "CommandFuncDef.h"
#include "CommandIF.h"
#include "CommandPrint.h"

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
    virtual int execute(int, int) = 0;
};

#endif //COMMAND_H

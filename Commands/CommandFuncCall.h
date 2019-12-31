/**
 * this class is for executing a function.
 * notice that there's CommandFuncDef for setting a function.
 *
 * @date 12/26/19
 * @author Rony 
 */

#ifndef COMMANDFUNCCALL_H
#define COMMANDFUNCCALL_H

#include "Command.h"

/**
 * Function Call Command
 */
class CommandFuncCall: public Command {
    int execute(int);
};


#endif //COMMANDFUNCCALL_H

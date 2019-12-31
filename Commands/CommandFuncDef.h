/**
 * this class is for setting a function. not for executing it.
 *
 *
 * @date 12/26/19
 * @author Rony 
 */

#ifndef COMMANDFUNCDEF_H
#define COMMANDFUNCDEF_H

#include "Command.h"

/**
 * Function Definition Command
 */
class CommandFuncDef: public Command {
    int execute(int);
};


#endif //COMMANDFUNCDEF_H

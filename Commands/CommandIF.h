/**
 * this class is for executing an if statement.
 *
 * @date 12/26/19
 * @author Rony 
 */

#ifndef COMMANDIF_H
#define COMMANDIF_H

#include "Command.h"

/**
 * If Condition Command
 */
class CommandIF: public Command {
    int execute(int);
};


#endif //COMMANDIF_H

//
// Created by rony on 12/26/19.
//

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

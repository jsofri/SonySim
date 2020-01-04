/**
 * this class is for a print command.
 *
 * @date 12/26/19
 * @author Rony 
 */

#ifndef COMMANDPRINT_H
#define COMMANDPRINT_H

#include "Command.h"

class CommandPrint: public Command {
    int execute(int);
};


#endif //COMMANDPRINT_H

/**
 * this class is a dummy command - just ignores the line.
 *
 * @authoer Rony
 * @date 12/28/19
 */

#ifndef COMMANDCOMMENT_H
#define COMMANDCOMMENT_H

#include "Command.h"

/**
 * Comment Command
 */
class CommandComment: public Command {
    int execute(int);
};


#endif //COMMANDCOMMENT_H

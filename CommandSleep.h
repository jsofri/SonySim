/**
 * Class for handling with sleep command.
 *
 * @author Yehonatan Sofri
 * @date 12.25.19
 */

#ifndef COMMANDSLEEP_H
#define COMMANDSLEEP_H

#include "GeneralData.h"

class CommandSleep : public Command {
public:
    int execute(int);
    CommandSleep();
    ~CommandSleep();
private:
    FloatFromString * _floatFromString;
};


#endif //COMMANDSLEEP_H

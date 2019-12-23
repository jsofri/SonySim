//
// Created by yehonatan on 23/12/2019.
//

#ifndef SONYSIM_COMMANDWHILE_H
#define SONYSIM_COMMANDWHILE_H

#include "GeneralData.h"
#include "Command.h"
class CommandWhile : public Command {
public:
    int execute(int);
    CommandWhile();
    ~CommandWhile() = default;
};


#endif //SONYSIM_COMMANDWHILE_H

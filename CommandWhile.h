/**
 * Class for handling a while command.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#ifndef COMMANDWHILE_H
#define COMMANDWHILE_H

#include "GeneralData.h"
#include "Command.h"
#include "Conditions/Condition.h"
#include "Conditions/ConditionFactory.h"

class CommandWhile : public Command {
public:
    int execute(int);
    void executeLoop();
    void cleanData();
    void setCondition(int);
    void setCommands();
    void setCommand(int index);
    CommandWhile();
    ~CommandWhile();
private:
    list<Command*> commands;
    Condition * condition;
    ConditionFactory * factory;
    int start_of_scope;
};

#endif //COMMANDWHILE_H

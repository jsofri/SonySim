/**
 * Class for handling a while command.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#ifndef COMMANDWHILE_H
#define COMMANDWHILE_H

#include "../GeneralData.h"

class CommandWhile : public Command {
public:
    int execute(int);
    void cleanData();
    void setCondition(int);
    CommandWhile() = default;
    ~CommandWhile();
private:
    list<Command*> _commands;
    Condition * _condition;
    ConditionFactory * _factory;
    int _start_of_scope;
};

#endif //COMMANDWHILE_H

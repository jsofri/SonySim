//
// Created by rony on 12/19/19.
//

#ifndef COMMAND_H
#define COMMAND_H

using namespace std;

/**
 * Command Class
 *
 * Note: Abstract class
 */
class Command {

    public:
    /**
     * execute the command
     */
    virtual void execute() = 0;

    /**
     * destructor
     */
    ~Command() {}
};

#endif //COMMAND_H

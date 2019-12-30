/**
 * class for create and run client thread.
 *
 * @author Yehonatan Sofri
 * @date 12.26.19
 */

#ifndef COMMANDCLIENT_H
#define COMMANDCLIENT_H

#include "Command.h"

class CommandClient : public Command {
public:
    int execute(int);
    void runClient();
    string setMessage();
    CommandClient() = default;
    ~CommandClient() = default;
private:
    string _ip;
    int    _port;
};


#endif //COMMANDCLIENT_H

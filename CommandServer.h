//
// Created by yehonatan on 25/12/2019.
//

#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include "GeneralData.h"

class CommandServer : public Command {
public:
    void setServer();
    int execute(int);
    void createSocket();
    void bindSocket();
    void listenAndAccept();
    CommandServer();
    ~CommandServer();
private:
    int _port;
};


#endif //COMMANDSERVER_H

//
// Created by yehonatan on 25/12/2019.
//

#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include "GeneralData.h"

class CommandServer : public Command {
public:
    void runServer();
    int execute(int);
    void createSocket();
    void bindSocket();
    void listenAndAccept();
    string convertToString(char*);
    CommandServer();
    ~CommandServer();
private:
    int _port;
};


#endif //COMMANDSERVER_H

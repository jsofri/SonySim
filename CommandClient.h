//
// Created by yehonatan on 26/12/2019.
//

#ifndef SONYSIM_COMMANDCLIENT_H
#define SONYSIM_COMMANDCLIENT_H

#include "GeneralData.h"

class CommandClient {
public:
    int execute(int);
    void runClient();
    CommandClient() = default;
    ~CommandClient() = default;
private:
    string _ip;
    int    _port;
};


#endif //SONYSIM_COMMANDCLIENT_H

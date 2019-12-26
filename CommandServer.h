/**
 * class for create and run server thread.
 *
 * @author Yehonatan Sofri
 * @date 12.26.19
 */

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

/**
 * This header file contains general `include`s and `define`s for the whole program
 *
 * @author Yehonatan Sofri
 * @date 19.12.19
 */

#ifndef GENERALDATA_H
#define GENERALDATA_H

#include <iostream>
#include <string>
#include <cstring>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <regex>
#include <thread>
#include <chrono>
#include <fstream>
#include "mutex"

#include "SymbolTable.h"
#include "UpdateSimulatorQueue.h"
#include "../Commands/Command.h"

// defines for the VarData struct
#define NO_ONE 0
#define CLIENT 1
#define SIMULATOR 2

// defines for the commands
#define COM_VAR "var"
#define COM_WHILE "while"
#define COM_IF "if"
#define COM_FUNC_DEF "funcDef"
#define COM_FUNC_CALL "funcCall"
#define COM_PRINT "print"
#define COM_SLEEP "sleep"
#define COM_SERVER "server"
#define COM_CLIENT "client"
#define COM_COMMENT "comment"

// default input file name
#define FILE_NAME "./fly_with_func.txt"

using namespace std;

#endif //GENERALDATA_H

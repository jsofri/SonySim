/**
 * this header files contains general data for the whole program.
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
#include <unordered_map>

#include <pthread.h>

#include <fstream>
#include <regex>

#include "Commands/Command.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

//defines for the VarData struct
#define NO_ONE 0
#define CLIENT 1
#define SIMULATOR 2

#define COM_VAR "var"
#define COM_WHILE "while"
#define COM_IF "if"
#define COM_FUNC_DEF "funcDef"
#define COM_FUNC_CALL "funcCall"
#define COM_UPDATE "update"
#define COM_PRINT "print"
#define COM_SLEEP "sleep"
#define COM_OPEN_SERVER "openServer"
#define COM_CONNECT "connect"

//data that is refers to a specific variable - is used in symbol_table
typedef struct VarData {
    string reference;
    float value;
    short updater;//0 = no one, 1 = client, 2 = simulator
} VarData;


// the lexer array of tokens
extern vector<string> tokens;

// map that stores:
// (1) function name
// (2) start & end indexes of definition in the lexer token array
// (3) map parameters names and values
extern unordered_map<string, pair<pair<int, int>, vector<string>>> funcMap;

extern unordered_map<string, Command*> cmdMap;

//symbol table of the program parsing process
extern SymbolTable symbol_table;

// key: index in XML, value: variable name in symbol table
// Note: this map stores only var names that are SIMULATOR-wrapped (i.e. `<-` binding)
extern unordered_map<int, vector<string>> xmlIndexToVarMap;

// key: simulator reference, value: index in XML
extern unordered_map<string, int> xmlRefToIndexMap;


#endif //GENERALDATA_H

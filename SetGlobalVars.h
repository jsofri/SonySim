//
// Created by rony on 12/28/19.
//

#ifndef SETGLOBALVARS_H
#define SETGLOBALVARS_H

#include "Commands/Command.h"
#include "Commands/CommandWhile.h"
#include "Commands/CommandVar.h"
#include "Commands/CommandIF.h"
#include "Commands/CommandFuncDef.h"
#include "Commands/CommandFuncCall.h"
#include "Commands/CommandPrint.h"
#include "Commands/CommandSleep.h"
#include "Commands/CommandServer.h"
#include "Commands/CommandClient.h"
#include "Commands/CommandComment.h"

unordered_map<int, vector<string>> xmlIndexToVarMap;
unordered_map<string, pair<int, vector<string>>> funcMap;
vector<string> tokens;
SymbolTable          symbol_table;
UpdateSimulatorQueue updateSimulatorQueue;
thread               client;
thread               server;
bool                 mainIsParsing = true;

unordered_map<string, Command*> cmdMap = {{COM_VAR, new CommandVar()},
                                          {COM_WHILE, new CommandWhile()},
                                          {COM_IF, new CommandIF()},
                                          {COM_FUNC_DEF, new CommandFuncDef()},
                                          {COM_FUNC_CALL, new CommandFuncCall()},
                                          {COM_PRINT, new CommandPrint()},
                                          {COM_SLEEP, new CommandSleep()},
                                          {COM_SERVER, new CommandServer()},
                                          {COM_CLIENT, new CommandClient()},
                                          {COM_COMMENT, new CommandComment()}};

unordered_map<string, int> xmlRefToIndexMap =  {{"/instrumentation/airspeed-indicator/indicated-speed-kt", 1},
                                                {"/sim/time/warp", 2},
                                                {"/controls/switches/magnetos", 3},
                                                {"/instrumentation/heading-indicator/offset-deg", 4},
                                                {"/instrumentation/altimeter/indicated-altitude-ft", 5},
                                                {"/instrumentation/altimeter/pressure-alt-ft", 6},
                                                {"/instrumentation/attitude-indicator/indicated-pitch-deg", 7},
                                                {"/instrumentation/attitude-indicator/indicated-roll-deg", 8},
                                                {"/instrumentation/attitude-indicator/internal-pitch-deg", 9},
                                                {"/instrumentation/attitude-indicator/internal-roll-deg", 10},
                                                {"/instrumentation/encoder/indicated-altitude-ft", 11},
                                                {"/instrumentation/encoder/pressure-alt-ft", 12},
                                                {"/instrumentation/gps/indicated-altitude-ft", 13},
                                                {"/instrumentation/gps/indicated-ground-speed-kt", 14},
                                                {"/instrumentation/gps/indicated-vertical-speed", 15},
                                                {"/instrumentation/heading-indicator/indicated-heading-deg", 16},
                                                {"/instrumentation/magnetic-compass/indicated-heading-deg", 17},
                                                {"/instrumentation/slip-skid-ball/indicated-slip-skid", 18},
                                                {"/instrumentation/turn-indicator/indicated-turn-rate", 19},
                                                {"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 20},
                                                {"/controls/flight/aileron", 21},
                                                {"/controls/flight/elevator", 22},
                                                {"/controls/flight/rudder", 23},
                                                {"/controls/flight/flaps", 24},
                                                {"/controls/engines/engine/throttle", 25},
                                                {"/controls/engines/current-engine/throttle", 26},
                                                {"/controls/switches/master-avionics", 27},
                                                {"/controls/switches/starter", 28},
                                                {"/engines/active-engine/auto-start", 29},
                                                {"/controls/flight/speedbrake", 30},
                                                {"/sim/model/c172p/brake-parking", 31},
                                                {"/controls/engines/engine/primer", 32},
                                                {"/controls/engines/current-engine/mixture", 33},
                                                {"/controls/switches/master-bat", 34},
                                                {"/controls/switches/master-alt", 35},
                                                {"/engines/engine/rpm", 36}};

#endif //SETGLOBALVARS_H

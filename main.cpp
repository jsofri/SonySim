//
// Created by Rony Utevsky and Yehonatan Sofri on 12/19/19.
//

#include "GeneralData.h"

int main(int argc, char const *argv[]) {
    // check if a file name was given
    if (argc != 2) {
        cerr << "Error: no file was given as input!" << endl;
        exit(-1);
    }

    // make tokens
    string filename = argv[1];
    Lexer::makeTokens(filename);

    /*
    Parser parser;
    parser.parse();

    // mark that the parsing process is done so that the server can close the socket
    mainIsParsing = false;
    
    // wait for threads to finish
    client.join();
    server.join();

    // delete allocated commands in map
    deleteAllData();
     */

    return 0;
}

void setGlobalVars() {
    cmdMap = {{COM_VAR, new CommandVar()},
              {COM_WHILE, new CommandWhile()},
              {COM_IF, new CommandIF()},
              {COM_FUNC_DEF, new CommandFuncDef()},
              {COM_FUNC_CALL, new CommandFuncCall()},
              {COM_UPDATE, new CommandUpdate()},
              {COM_PRINT, new CommandPrint()},
              {COM_SLEEP, new CommandSleep()},
              {COM_OPEN_SERVER, new CommandOpenServer()},
              {COM_CONNECT, new CommandConnect()}};

    xmlRefToIndexMap = {{"/instrumentation/airspeed-indicator/indicated-speed-kt", 1},
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
}
/**
 * class for create and run server thread - listen to simulator.
 *
 * @author Yehonatan Sofri
 * @date 12.26.19
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "CommandServer.h"
#include "../DataManagement/Lexer.h"
#include "../DataManagement/FloatFromString.h"

#define BUFFER 1024

/**
 * executing a command of openDataServer.
 *
 * @param index in vector of token
 * @return int - first string after this command line
 */
int CommandServer::execute(int index) {

    this -> _port = (int) FloatFromString::calculateString(tokens[index + 1]);

    server = thread(&CommandServer::runServer, this);

    return index + 3;
}

/**
 * run a server.
 * The server thread runs it.
 */
void CommandServer::runServer() {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[BUFFER];
    if (socketfd == -1) {

        cerr << "Could not create a socket" << endl;
        exit(EXIT_FAILURE);

    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in meanVarData                     var_data;s IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(_port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << endl;
        exit(EXIT_FAILURE);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        cerr << "Error during listening command" << endl;
        exit(EXIT_FAILURE);
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    while (client_socket == -1) {
        client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);
    }

    //uncomment if testing
    //cout << "Simulator connected as client!" << endl;

    string str;
    while(mainIsParsing) {
        read(client_socket, buffer, BUFFER);
        string values = convertToString(buffer);

        // regex
        if (!values.empty()) {
            this->handleCSV(values);
        }
    }

    close(socketfd); //closing the listening socket
}

/**
 * converts the array of chars that comes from the buffer to a string that has 36 floats.
 * 
 * @param a the char array that comes from the buffer
 * @return the string with 36 float values
 */
string CommandServer::convertToString(char* a)
{
    int i = 0;
    string s;
    
    // read until first \n and check that every char is legal
    while (a[i] != '\n' && this->isCSVChar(a[i])) {
        s += a[i];
        i++;
    }

    // if there are indeed 36 floats
    if(Lexer::doRegex(s, PATTERN).size() == xmlRefToIndexMap.size()) {
        return s;
    }
    
    // if we haven't found 36 floats, we check again for the next chunk of chars between \n and another \n
    s = "";

    // read until first \n and check that every char is legal
    while (a[++i] != '\n' && this->isCSVChar(a[i])) {
        s += a[i];
    }

    // if there are indeed 36 floats
    if(Lexer::doRegex(s, PATTERN).size() != xmlRefToIndexMap.size()) {
        s = "";
    }

    return s;
}

/**
 * parse the string and extract the 36 float values using regex
 * 
 * @param string the string with 36 float values
 */
void CommandServer::handleCSV(string values) {
    string pattern = PATTERN;
    // get the matches using regex
    vector<string> matches = Lexer::doRegex(values, pattern);

    // start index at 1 because `xmlIndexToVarMap` starts at 1 
    int index = 1;
    
    for (string match : matches) {
        // get the relevant vars that refer to the specific reference of simulator variable
        vector<string> vars = xmlIndexToVarMap[index];
        
        for (string var : vars) {
            VarData vdata = symbol_table.get(var);

            // update var in `symbol table` only if the updater is the simulator
            if (vdata.updater == SIMULATOR) {
                float val = stof(match);
                symbol_table.update(var, val);
            }
        }
        index++;
    }
}

/**
 * check if a char is a legal char in the CSV
 * 
 * @param c the char to check
 * @return true if legal char
 */
bool CommandServer :: isCSVChar(char c) {
    bool boolean = false;

    // char can be: [0-9.-\n,]
    if ((c >= '0' && c <= '9') || c == '.' || c == '-' || c == '\n' || c == ',') {
        boolean = true;
    }

    return boolean;
}

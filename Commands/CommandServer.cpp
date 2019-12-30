/**
 * class for create and run client thread.
 *
 * @author Yehonatan Sofri
 * @date 12.26.19
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "CommandServer.h"
#include "../Lexer.h"
#include "../FloatFromString.h"

#define BUFFER 1024

/**
 * Command Abstract class method.
 * executing a command of openDataServer.
 *
 * @param index in vector of token
 * @return int - first string after this command line
 */
int CommandServer::execute(int index) {
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (tokens[index] == "\n") {
        return execute(index + 1);
    }

    this -> _port = stoi(tokens[index + 1]);

    server = thread(&CommandServer::runServer, this);

    return index + 3;
}

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

    cout << "Simulator connected as client!" << endl;

    int t = 0;
    string str;
    while(mainIsParsing) {
        int valread = read( client_socket , buffer, BUFFER);
        string values;
        int size_of_buffer = sizeof(buffer) / sizeof(char);

        values = convertToString(buffer);

        // regex
        if (!values.empty()) {
            this->handleCSV(values);
        }
    }

    close(socketfd); //closing the listening socket
}

string CommandServer::convertToString(char* a)
{
    int i = 0, countBr = 0;
    string s;

    while (a[i] != '\n' && this->isCSVChar(a[i])) {
        s += a[i];
        i++;
    }

    if(Lexer::doRegex(s, PATTERN).size() == xmlRefToIndexMap.size()) {
        return s;
    }

    s = "";

    while (a[++i] != '\n' && this->isCSVChar(a[i])) {
        s += a[i];
    }

    if(Lexer::doRegex(s, PATTERN).size() != xmlRefToIndexMap.size()) {
        s = "";
    }

    return s;
}

void CommandServer::handleCSV(string values) {
    string pattern = PATTERN;
    vector<string> matches = Lexer::doRegex(values, pattern);

    int index = 1;
    for (string match : matches) {
        vector<string> vars = xmlIndexToVarMap[index];
        for (string var : vars) {

            if (var == "rpm") {
                float v = stof(match);
                if (v > 400) {
                    cout << "rpm: " << v;
                }
            }

            VarData vdata = symbol_table.get(var);


            //cout << "###" << var << " " << match << endl;

            if (vdata.updater == SIMULATOR) {
                float val = stof(match);
                symbol_table.update(var, val);
                if (var == "rpm") {
                    cout << "rpm: " << val << endl;
                }
                //cout << "updated key: " << var << " " << match << endl;
            }
        }

        index++;
    }
}


bool CommandServer :: isCSVChar(char c) {
    bool boolean = false;

    if ((c >= '0' && c <= '9') || c == '.' || c == '-' || c == '\n' || c == ',') {
        boolean = true;
    }

    return boolean;
}
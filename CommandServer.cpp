//
// Created by yehonatan on 25/12/2019.
//

#include "CommandServer.h"

int CommandServer::execute(int index) {
    this -> _port = stoi(tokens[index + 1]);

    server = thread(&CommandServer::runServer, this);

    return index + 3;
}

void CommandServer::runServer() {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[1024];
    if (socketfd == -1) {

        throw "Could not create a socket";

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
        throw "Could not bind the socket to an IP";
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        throw "Error during listening command";
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    if (client_socket == -1) {
        throw "Error accepting client";
    }

    int t = 0;
    string str;
    while(mainIsParsing) {
        int valread = read( client_socket , buffer, 1024);
        string values;
        int size_of_buffer = sizeof(buffer) / sizeof(char);

        values = convertToString(buffer);

        this -> handleCSV(values);//regex
    }

    close(socketfd); //closing the listening socket
}

string CommandServer::convertToString(char* a)
{
    int i = 0;
    string s = "";

    while (a[i] != '\n') {
        s = s + a[i];

        i++;
    }

    return s;
}
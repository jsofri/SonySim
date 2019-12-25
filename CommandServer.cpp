//
// Created by yehonatan on 25/12/2019.
//

#include "CommandServer.h"

int CommandServer::execute(int index) {
    this -> _port = stoi(tokens[index + 1]);

    thread(foo);

    return 3;
}

void CommandServer::setServer() {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {

        throw "Could not create a socket";

    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
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

    close(socketfd); //closing the listening socket

    //reading from client
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    //writing back to client
    char *hello = "Hello, I can hear you! \n";
    send(client_socket, hello, strlen(hello), 0);
}
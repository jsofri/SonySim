//
// Created by yehonatan on 26/12/2019.
//

#include "CommandClient.h"

int CommandClient::execute(int index) {
    string ip_address = tokens[++index];
    string str;

    str = str.substr(1, strlen(str.c_str()) - 2);

    this -> _ip = str;
    this -> _port = stoi(tokens[++index]);

    client = thread(&CommandClient::runClient, this);

    return index + 2;
}

void CommandClient::runClient() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        //error
        throw "Client could not create a socket";
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(this -> _port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        throw "Client could not connect to host server";
    }

    while (mainIsParsing) {
        if(!updateSimulatorQueue.isEmpty()) {
            VarData var_data;
            string message;
            /*
            //if here we made a connection
            char hello[] = "Hi from client";
             */
            int is_sent = send(client_socket, message, 20, 0);
            if (is_sent == -1) {
                cerr << "Error sending message" << std::endl;
            }
        }
    }

    close(client_socket);
}

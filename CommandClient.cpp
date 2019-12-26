/**
 * class for create and run client thread.
 *
 * @author Yehonatan Sofri
 * @date 12.26.19
 */

#include "CommandClient.h"

/**
 * Command Abstract class method.
 * executing a command of connectControlClient.
 *
 * @param index in vector of token
 * @return int - first string after this command line
 */
int CommandClient::execute(int index) {
    string ip_address = tokens[++index];
    string str;

    str = str.substr(1, strlen(str.c_str()) - 2);

    this -> _ip = str;
    this -> _port = stoi(tokens[++index]);

    client = thread(&CommandClient::runClient, this);

    return index + 2;
}

/**
 * create a socket and update with telnet operations.
 * updates depend on data in the updateSimulatorQueue of program.
 *
 * @test 12.26.19 by YS with Simulator
 */
void CommandClient::runClient() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        //error
        cerr << "Client could not create a socket" <<endl;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(this -> _ip.c_str());
    address.sin_port = htons(this -> _port);

    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Client could not connect to host server" << endl;
    }
    while (mainIsParsing) {
        if (updateSimulatorQueue.isEmpty()) {
            string message = this -> setMessage();
            int is_sent = send(client_socket, message.c_str(), strlen(message.c_str()), 0);

            if (is_sent == -1) {
                cerr << "Error sending message" << std::endl;
            }
        }
    }
}

/**
 * take out one struct from updateSimulatorQueue and send a set command to simulator.
 *
 * @test 12.26.19 by YS with Simulator
 * @return string of a telnet command to simulator
 */
string CommandClient::setMessage() {
    VarData var_data;
    string  reference;
    string  value;

    var_data = updateSimulatorQueue.dequeue();
    reference = var_data.reference;
    value = to_string(var_data.value);

    return "set " + reference + " " + value + "\r\n";
}
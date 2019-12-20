//
// Created by rony on 12/19/19.
//

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <vector>
#include <map>

#include <pthread.h>

#include <fstream>

#include "lexer.h"
#include "command.h"
#include "parser.h"

using namespace std;

int main(int argc, char const *argv[]) {
    // check if file name was given
    if (argc != 2) {
        //error
    }

    string filename = argv[1];
    Lexer lexer(filename);
    // make tokens
    lexer.makeTokens();
    // get the token array
    vector<string> tokens = lexer.getTokens();
    // delete lexer
    delete lexer;

    Parser parser(tokens);
    parser.parse();


    return 0;
}
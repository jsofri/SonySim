//
// Created by rony on 12/19/19.
//

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

#include "GeneralData.h"
#include "lexer.h"
#include "Command.h"
#include "parser.h"
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
    // delete lexer
    delete lexer;

    Parser parser();
    parser.parse();


    return 0;
}
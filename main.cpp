/**
 * This file runs the program.
 * 
 * @date 12/21/19
 * @author Rony Utevsky and Yehonatan Sofri
 **/

#include "GeneralData.h"
#include "GlobalVars.h"
#include "Lexer.h"
#include "Parser.h"
#include "SetGlobalVars.h"


int main(int argc, char const *argv[]) {
    // check if a file name was given
    if (argc != 2) {
        cerr << "Error: no file was given as input!" << endl;
        exit(-1);
    }

    // make tokens
    string filename = argv[1];
    Lexer::makeTokens(filename);

    // parse the code and execute the commands
    Parser parser;
    parser.parse();


    // mark that the parsing process is done so that the server can close the socket
    mainIsParsing = false;
    
    // wait for threads to finish
    client.join();
    server.join();

    // delete allocated commands in map
    // deleteAllData();

    return 0;
}

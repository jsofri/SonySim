//
// Created by rony on 12/19/19.
//

#include "GeneralData.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char const *argv[]) {
    // check if a file name was given
    if (argc != 2) {
        // error
    }

    string filename = argv[1];
    Lexer lexer(filename);
    // make tokens
    lexer.makeTokens();
    // delete lexer
    delete lexer; // @Rony reduntant?

    Parser parser;
    parser.parse();


    return 0;
}
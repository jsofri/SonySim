//
// Created by Rony Utevsky and Yehonatan Sofri on 12/19/19.
//

#include "CommandVar.h"


int main(int argc, char const *argv[]) {

    //testing CommandVar
    int index = 0;

    CommandVar varCommand;

    index += varCommand.execute(index);

    index += varCommand.execute(index);

    cout <<index<<endl;
    //end of test



    /*
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

*/
    return 0;
}
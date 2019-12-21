//
// Created by rony on 12/21/19.
//

#include "GeneralData.h"
#include "parser.h"

int CommandPrint :: execute(int index) {
    auto it = tokens.begin();
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (*it == "\n") {
        index++;
    }

    cout << *(it + index + 1) << endl;
    return index + 1;
}


int CommandFuncDef :: execute(int index) {
    Parser parser;
    parser.parse(index);
}
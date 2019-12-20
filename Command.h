//
// Created by yehonatan on 19/12/2019.
//

#ifndef ACPROJECT_COMMAND_H
#define ACPROJECT_COMMAND_H


#include "SymbolTable.h"
/*
 * Abstract class for all command objects.
 * contain a data member of index_counter - counts number of tokens in the tokens_array of tokens.
 * execute() must be implemented by classes.
 */
class Command {
public:
    //should return index_counter
    virtual int execute(int) = 0;
protected:
    int index_counter = 0;
};
#endif //ACPROJECT_COMMAND_H

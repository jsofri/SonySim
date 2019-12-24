/**
 * Class for handling a while command.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "CommandWhile.h"

CommandWhile::CommandWhile() {
    this -> factory = new ConditionFactory();
}

int CommandWhile::execute(int index) {
    this -> cleanData();
    this -> setCondition(index);

    //3 strings for condition, 4th for "{"
    this -> start_of_scope = index += 4;
    indexCounter = 4;

    symbol_table.newTable();

    do {
        indexCounter++;
    } while (tokens[++index][0] != '}');

    this -> end_of_scope = index;

    this -> executeLoop();

    return indexCounter;
}

void CommandWhile::executeLoop() {
    while (this -> condition ->isTrue()) {
        //lex?
    }
}

void CommandWhile::cleanData() {
    this ->condition = nullptr;
    this -> indexCounter = 0;
}

void CommandWhile::setCondition(int index) {
    this -> condition = this -> factory -> setCondition(tokens[index],
                                                        tokens[++index], tokens[++index]);
}

CommandWhile::~CommandWhile() {
    delete(this -> condition);
    delete(this -> factory);
}
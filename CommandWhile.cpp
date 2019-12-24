/**
 * Class for handling a while command.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "CommandWhile.h"
#include "CommandVar.h"

CommandWhile::CommandWhile() {
    this -> factory = new ConditionFactory();
}

int CommandWhile::execute(int index) {
    this -> cleanData();
    this -> setCondition(index);

    this -> start_of_scope = index += 4; //3 strings for condition, 4th for "{"/////////////////////////////////////

    symbol_table.newTable();

    this -> setCommands();              //incrementing indexCounter
    this -> executeLoop();

    symbol_table.deleteTable();

    return this -> indexCounter;
}

void CommandWhile::setCommands() {
    int index = start_of_scope;

    while (tokens[index][0] != '}') {
        tokens[index];
        //figure put first word
        while (tokens[++index][0] != '\n') {}
        ++index;
    }

    this -> indexCounter = (index - start_of_scope) + 4?5; //3 strings of condition, 4th for "{"////////////////////
}

void CommandWhile::setCommand(int index) {
    string first_word = tokens[index];
    string second_word = tokens[index+1];

    if (first_word == "sleep") {
        this -> commands.push_back(new CommandSleep());
    } else if (first_word == "print") {
        this -> commands.push_back(new CommandPrint());
    } else if ((first_word == "var") ||(second_word == "=")) {
        this ->commands.push_back(new CommandVar());
    }
}

void CommandWhile::executeLoop() {
    int index;

    while (this -> condition ->isTrue()) {
        index = start_of_scope;

        for (Command * command : this -> commands) {
            index = command -> execute(index);
        }
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
    delete (this->condition);
    delete (this->factory);

    while (!(this->commands.empty())) {
        this->commands.pop_front();
    }
}

/**
 * Class for handling a while command.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "CommandWhile.h"
#include "CommandVar.h"
#include "CommandSleep.h"

/**
 * Constructor
 */
CommandWhile::CommandWhile() {
    this -> _factory = new ConditionFactory();
}

/**
 * set a list of commands anf run it while the condition is true.
 *
 * @param index in vector<string> tokens
 * @return int - number of string in vector associated with while block.
 */
int CommandWhile::execute(int index) {
    this -> cleanData();
    this -> setCondition(index);

    this -> _start_of_scope = index += 5;

    symbol_table.newTable();

    this -> setCommands();              //incrementing indexCounter

    this -> executeLoop();

    symbol_table.deleteTable();

    return this -> indexCounter;
}

/**
 * set list of commands using helper function.
 * update indexCounter to end of block in tokens.
 */
void CommandWhile::setCommands() {
    int index = _start_of_scope;

    while (tokens[index][0] != '}') {
        this->setCommand(index);

        //no inside scopes are promised, no need to check "{"
        while (tokens[++index][0] != '\n') {}
        ++index;
    }

    this -> indexCounter = (index - _start_of_scope) + 4 ? 5; //3 strings of _condition, 4th for "{"////////////////////
}

/**
 * set a new command in the beginning of the list.
 * choose command by the token in the index.
 *
 * @param index position in global variable tokens
 */
void CommandWhile::setCommand(int index) {
    string first_word = tokens[index];
    string second_word = tokens[index+1];

    if (first_word == "sleep") {
        this -> _commands.push_back(new CommandSleep());
    } else if (first_word == "print") {
        this -> _commands.push_back(new CommandPrint());
    } else if ((first_word == "var") ||(second_word == "=")) {
        this ->_commands.push_back(new CommandVar());
    } else {////////////////////////////////////////////referring to a CommandFunc
        throw "invalid command in while loop";
    }
}

/**
 * run the commands in the list while the condition is true.
 */
void CommandWhile::executeLoop() {
    int index;

    while (this -> _condition ->isTrue()) {
        index = _start_of_scope;

        for (Command * command : this -> _commands) {
            index += command -> execute(index);
        }
    }
}

/**
 * cleans data members.
 */
void CommandWhile::cleanData() {
    this ->_condition = nullptr;
    this -> indexCounter = 0;
}

/**
 * create a condition using ConditionFactory.
 * @param index in the gloval variable tokens - vector of strings
 */
void CommandWhile::setCondition(int index) {
    this -> _condition = this -> _factory -> setCondition(tokens[index],
                                                          tokens[++index], tokens[++index]);
}

/**
 * Destructor - deleting data members.
 */
CommandWhile::~CommandWhile() {
    delete (this->_condition);
    delete (this->_factory);

    while (!(this->_commands.empty())) {
        this->_commands.pop_front();
    }
}

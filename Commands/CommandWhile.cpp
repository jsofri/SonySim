/**
 * Class for handling a while command.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "CommandWhile.h"
#include "../Conditions/ConditionFactory.h"
#include "../Parser.h"
#include "../Lexer.h"


/**
 * set a list of commands anf run it while the condition is true.
 *
 * @param index in vector<string> tokens
 * @return int - number of string in vector associated with while block.
 */
int CommandWhile::execute(int index) {
    // if it's a new line string (maybe a leftover from the last command), then move on to the next token
    if (tokens[index] == "\n") {
        return execute(index + 1);
    }

    Parser parser;
    int closing_bracket = Lexer::findClosingBracketIndex(index);

    this -> cleanData();
    this -> setCondition(index + 1);

    symbol_table.newTable();

    while (this -> _condition->isTrue()) {
        parser.parse(index + 6, closing_bracket);
    }

    symbol_table.deleteTable();

    return closing_bracket + 2;
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
    ConditionFactory factory;
    this -> _condition = factory.setCondition(tokens[index], tokens[index + 1], tokens[index + 2]);
}

/**
 * Destructor - deleting data members.
 */
CommandWhile::~CommandWhile() {
    delete (this->_condition);

    while (!(this->_commands.empty())) {
        this->_commands.pop_front();
    }
}
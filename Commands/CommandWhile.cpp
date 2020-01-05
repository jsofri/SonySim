/**
 * Class for handling a while command.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "CommandWhile.h"
#include "../Conditions/ConditionFactory.h"
#include "../DataManagement/Parser.h"
#include "../DataManagement/Lexer.h"


/**
 * set a list of commands anf run it while the condition is true.
 *
 * @param index in vector<string> tokens
 * @return int - number of string in vector associated with while block.
 */
int CommandWhile::execute(int index) {

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

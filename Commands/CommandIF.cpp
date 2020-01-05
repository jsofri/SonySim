/**
 * this class is for executing an if statement.
 *
 * @date 12/26/19
 * @author Rony 
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "CommandIF.h"
#include "../Conditions/ConditionFactory.h"
#include "../DataManagement/Lexer.h"
#include "../DataManagement/Parser.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandIF :: execute(int index) {

    ConditionFactory factory;
    Condition* cond = factory.setCondition(tokens[index+1], tokens[index+2], tokens[index+3]);
    index += 3;

    int closingBracket = Lexer::findClosingBracketIndex(index);

    if (cond -> isTrue()) {
        // create new symbol table for the new scope
        symbol_table.newTable();

        // parse the function
        Parser parser;
        parser.parse(index + 1, closingBracket);

        symbol_table.deleteTable();
    }

    return closingBracket + 2;
}

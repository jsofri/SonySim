/**
 * this class is for setting a function. not for executing it.
 *
 *
 * @date 12/26/19
 * @author Rony 
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "CommandFuncDef.h"
#include "../DataManagement/Lexer.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandFuncDef :: execute(int index) {

    string func = tokens[index];
    auto& params = funcMap[func].second;

    // look for param names
    while (tokens[++index] != "\n") {
        if (tokens[index] != "var" && tokens[index] != "{") {
            string param = tokens[index];

            // check if iilegal var name
            if (!Lexer::isLegalVar(param)) {
                throw "Error: Illegal parameter name in function";
            }

            // push parameter
            params.push_back(param);
        }
    }

    // find the index of the end of the function's definition
    int closingBracket = Lexer::findClosingBracketIndex(--index);
    return closingBracket;
}

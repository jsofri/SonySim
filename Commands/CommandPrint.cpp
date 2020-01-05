/**
 * this class is for a print command.
 *
 * @date 12/26/19
 * @author Rony 
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "CommandPrint.h"
#include "../DataManagement/Lexer.h"
#include "../DataManagement/FloatFromString.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandPrint :: execute(int index) {

    string print = tokens[++index];

    // check if not string
    if (Lexer::trim(print, '"') == print) {
        float value = FloatFromString::calculateString(print);
        cout << value << endl;
    } else {
        cout << Lexer::trim(print, '"') << endl;
    }

    return index + 2;
}

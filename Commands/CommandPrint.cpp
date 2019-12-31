/**
 * this class is for a print command.
 *
 * @date 12/26/19
 * @author Rony 
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "CommandPrint.h"
#include "../Lexer.h"

/**
 * Interpret and execute.
 *
 * @param index index in the vector
 * @return new index counter in the vector that will be passed to the next command
 */
int CommandPrint :: execute(int index) {

    string print = tokens[++index];

    // check if it's a variable
    if (Lexer::isLegalVar(print)) {
        if (!symbol_table.exists(print)) {
            throw "Error: unknown variable passed to Print";
        }
        float value = symbol_table.get(print).value;
        cout << value << endl;
    } else {
        // remove leading and trailing quotes
        string value = Lexer::trim(print, '"');
        // print the valflue
        cout << value << endl;
    }
    
    return index + 2;
}

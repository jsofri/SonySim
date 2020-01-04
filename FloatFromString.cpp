/**
 * This class is responsible for getting a string and returning a float - the value that the string represent.
 * The string can be either a number, a veriable or an expression.
 *
 * @author Yehonatan Sofri
 * @date 24.12.19
 */

#include "GeneralData.h"
#include "GlobalVars.h"
#include "FloatFromString.h"
#include "Lexer.h"

using namespace std;

/**
 * get a string and return the number it represents.
 *
 * @param str string that can be calculated to a number.
 * @return value in the string.
 */
float FloatFromString::calculateString(string str) {
    str = delSpaces(str);

    // if number
    if (isNumber(str)) {
        return stof(str);
    }
    // if variable
    else if (isVar(str)) {
        // if exists in symbol table
        if (symbol_table.exists(str)) {
            return symbol_table.get(str).value;
        } else {
            return 0; //uninitialized variable
        }
    }
    // if expression
    else if (isExpression(str)) {
        return floatFromExpression(str);
    }

    throw "can't convert string to a float";
}

/**
 * remove spaces from string.
 *
 * @param str reference to a string
 * @return string withour spaces
 */
string FloatFromString::delSpaces(string & str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

/**
 * get a string of arithmetic Expression and returns it's value.
 * @param str expression string
 * @return the float value of the expression
 */
float FloatFromString::floatFromExpression(string & str) {
    Interpreter *interpreter = new Interpreter();
    Expression *expression;
    float value;
    
    // update the local map of vars of the interpreter
    setVariables(interpreter, str);

    // check that the variables were set correctly
    try {
        expression = interpreter->interpret(str);
        value = expression->calculate();
        
        // delete allocated memory
        delete (expression);
        delete (interpreter);
    } catch (char *e) {
        if (expression != nullptr) {
            delete (expression);
        }
        if (interpreter != nullptr) {
            delete (interpreter);
        }

        cerr << e << endl;
    }

    return value;
}

/**
 * Extracts the variables names from the string and assigns to each the relevant value from symbol_table.
 *
 * @param interpreter Interpreter reference
 * @param str string that represents an arithmetic expression
 */
void FloatFromString::setVariables(Interpreter * & interpreter, string str) {
    VarData var_data;
    float value;

    auto matches = Lexer::doRegex(str, "([a-zA-z_][a-zA-z_\\d]*)|([\\d]+[.]?[\\d]+)|([\\d]+)|([!-_+#/*()])");

    // iterating on tokens in the infix string
    for (string match: matches) {

        if (Lexer::isLegalVar(match)) {

            try {
                var_data = symbol_table.get(match);
                value = var_data.value;
                interpreter->setVariable(match, value);

            } catch (char * e) {
                if (isNumber(match)) {
                    continue;
                } else {
                    throw "call to an unknown Variable in arithmetic expression";
                }
            }
        }
    }
}

/**
 * check if given string is a variable, by elimination.
 *
 * @param str string of a token
 * @return boolean - true or false
 */
bool FloatFromString::isVar(string & str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), ABC)) {
        return 1;
    }

    return 0;
}

/**
 * check if a given string is a float number.
 *
 * @test 12.16.19 by YS
 * @param str reference to a string.
 * @return bool - 1 if true, 0 if false
 */
bool FloatFromString::isNumber(string & str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), NUMBERS)) {
        return 1;
    }
    return 0;
}

/**
 * check if a given string is an expression by finding operators.
 * not perfect - assuming you went through isNumber beforehand.
 *
 * @test 12.16.19 by YS
 * @param str reference to a string.
 * @return bool - 1 if true, 0 if false
 */
bool FloatFromString::isExpression(string & str) {
    for (char & c : str) {
        switch (c) {
            case('*'):
            case ('/'):
            case('-'):
            case('+'):
            case('('):
            case(')'): return 1;
            default: continue;
        }
    }

    return 0;
}

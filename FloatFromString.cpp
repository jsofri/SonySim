/**
 * class is a generic object for all uses in program.
 * get a string and return a float - the value that the string represent.
 *
 * @author Yehonatan Sofri
 * @date 24.12.19
 */

#include "GeneralData.h"
#include "GlobalVars.h"
#include "FloatFromString.h"

using namespace std;

/**
 * get a string and return the number it represents.
 *
 * @param str string that can be calculated to a number.
 * @return value in the string.
 */
float FloatFromString::calculateString(string str) {
    str = delSpaces(str);

    if (isNumber(str)) {
        return stof(str);
    } else if (isVar(str)) {
        if (symbol_table.exists(str)) {
            return symbol_table.get(str).value;
        } else {
            return 0; //uninitialized variable
        }
    } else if (isExpression(str)) {
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
 * @param str
 * @return
 */
float FloatFromString::floatFromExpression(string & str) {
    Interpreter *interpreter = new Interpreter();
    Expression *expression;
    float value;

    setVariables(interpreter, str);

    try {
        expression = interpreter->interpret(str);

        value = expression->calculate();

        delete (expression);
        delete (interpreter);
    } catch (char *e) {
        if (expression != nullptr) {
            delete (expression);
        }
        if (interpreter != nullptr) {
            delete (interpreter);
        }
    }

    return value;
}

/**
 * set Variables in the given Interpreter.
 *
 * @param interpreter Interpreter reference
 * @param str string that represents an arithmetic expression
 */
void FloatFromString::setVariables(Interpreter * & interpreter, string str) {
    VarData var_data;
    float value;

    regex rgx("[a-zA-z_][a-zA-z_\\d]*|[\\d]+[.]?[\\d]+|[\\d]+|[!-_+#/*()]");

    std::regex_iterator<std::string::iterator> rit (str.begin(), str.end(), rgx);
    std::regex_iterator<std::string::iterator> rend;

    //iterating on tokens in the infix string
    while (rit!=rend) {

        if (strlen(str.c_str()) == strspn(str.c_str(), ABC)) {

            try {
                var_data = symbol_table.get(rit->str());

                value = var_data.value;

                interpreter->setVariable(rit->str(), value);

            } catch (char * e) {
                throw "call to an unknown Variable in arithmetic expression";
            }
        }

        ++rit;
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
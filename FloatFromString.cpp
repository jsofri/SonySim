//
// Created by yehonatan on 23/12/2019.
//

#include "FloatFromString.h"

using namespace std;

/**
 * get a string and return the number it represents.
 *
 * @param str string that can be calculated to a number.
 * @return value in the string.
 */
float FloatFromString::calculateString(string str) {
    if (this -> isNumber(str)) {
        return stof(str);
    } else if (this -> isVar(str)) {
        return symbol_table.get(str).value;
    } else if (this -> isExpression(str)) {
        return this -> floatFromExpression(str);
    }

    throw "can't convert string to a float";
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

    this->setVariables(interpreter, str);

    try {
        expression = interpreter->interpret(str);

        value = expression->calculate();

        delete (expression);
        delete (interpreter);
    } catch (const char *e) {
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

            } catch (const char * e) {
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
int FloatFromString::isVar(string & str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), ABC)) {
        return 1;
    }

    return 0;
}

/**
 * check if a given string is a float number.
 *
 * @param str reference to a string.
 * @return bool - 1 if true, 0 if false
 */
int FloatFromString::isNumber(string & str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), NUMBERS)) {
        return 1;
    }
    return 0;
}

/**
 *
 * @param str reference to a string.
 * @return bool - 1 if true, 0 if false
 */
int FloatFromString::isExpression(string & str) {
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
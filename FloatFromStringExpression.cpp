//
// Created by yehonatan on 23/12/2019.
//

#include "FloatFromStringExpression.h"

using namespace std;

float FloatFromStringExpression::calculateExpression(string str) {
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


void FloatFromStringExpression::setVariables(Interpreter * & interpreter, string str) {
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

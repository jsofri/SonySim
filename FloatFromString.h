//
// Created by yehonatan on 23/12/2019.
//

#ifndef FLOATFROMSTRINGEXPRESSION_H
#define FLOATFROMSTRINGEXPRESSION_H

#include "GeneralData.h"
#include <regex>
#include "Expressions/Interpreter.h"

#define NUMBERS "1234567890."
#define ABC "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwhyz_0123456789"

class FloatFromString {
public:
    float calculateString(string);
    FloatFromString() = default;
    ~FloatFromString() = default();
private:
    float floatFromExpression(string &);
    void setVariables(Interpreter * &, string);
    int isVar(string &);
    int isNumber(string &);
    int isExpression(string &);
};


#endif //FLOATFROMSTRINGEXPRESSION_H

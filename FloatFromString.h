//
// Created by yehonatan on 23/12/2019.
//

#ifndef FLOATFROMSTRING_H
#define FLOATFROMSTRING_H

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
    float  floatFromExpression(string &);
    void   setVariables(Interpreter * &, string);
    string delSpaces(string &str);
    bool   isVar(string &);
    bool   isNumber(string &);
    bool   isExpression(string &);
};

#endif //FLOATFROMSTRING_H

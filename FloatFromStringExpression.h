//
// Created by yehonatan on 23/12/2019.
//

#ifndef FLOATFROMSTRINGEXPRESSION_H
#define FLOATFROMSTRINGEXPRESSION_H

#include "GeneralData.h"
#include <regex>
#include "Expression/Interpreter.h"

#define ABC "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwhyz_0123456789"

class FloatFromStringExpression {
public:
    float calculateExpression(string);
private:
    void setVariables(Interpreter * &, string);
};


#endif //FLOATFROMSTRINGEXPRESSION_H

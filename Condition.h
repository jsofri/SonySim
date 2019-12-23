//
// Created by yehonatan on 23/12/2019.
//

#ifndef SONYSIM_CONDITION_H
#define SONYSIM_CONDITION_H

#include "GeneralData.h"
#include <Expression/Interpreter.h>
#include "FloatFromStringExpression.h"

class Condition {
public:
    virtual int execute(int);
    void calculateSides();
    float calculate(string &);
    Condition() = default;
    ~Condition() = default;
protected:
    string left_string;
    string right_string;
    float left_value;
    float right_value;
};
#endif //SONYSIM_CONDITION_H
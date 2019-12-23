//
// Created by yehonatan on 23/12/2019.
//

#include "Condition.h"

void Condition::calculateSides() {
    this -> left_value = this -> calculate(this -> left_string);
    this -> right_value = this -> calculate(this -> right_string);
}

float Condition::calculate(string & str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), "0123456789.")) {
        return stof(str);

    } else if (strlen(str.c_str()) == strspn(str.c_str(), ABC)) {//is variable
        VarData var_data = symbol_table.get(str);

        return var_data.value;
    }
    else { // is an expression
        FloatFromStringExpression floatFromStringExpression;

        return floatFromStringExpression.calculateExpression(str);
    }
}


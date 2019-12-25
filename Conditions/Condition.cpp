/**
 * abstract class for handling conditions in the code.
 *
 * @author Jhonny
 * @date 12.23.19
 */

#include "Condition.h"

/**
 * put value in the two sides of the conditions using calculate method.
 */
void Condition::calculateSides() {
    this -> left_value = this -> calculate(this -> left_string);
    this -> right_value = this -> calculate(this -> right_string);
}

/**
 * figures what is the string (float/ variable/ expression) and calculate it.
 *
 * @param str reference to a string of one of the sides
 * @return float - value of the string
 */
float Condition::calculate(string & str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), "0123456789.")) {
        return stof(str);

    } else if (strlen(str.c_str()) == strspn(str.c_str(), ABC)) {//is variable
        VarData var_data = symbol_table.get(str);

        return var_data.value;
    }
    else { // is an expression
        FloatFromString floatFromStringExpression;

        return floatFromStringExpression.calculateString(str);
    }
}


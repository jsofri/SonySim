/**
 * Factory for making Condition Object.
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "ConditionFactory.h"

/**
 * method get 3 strings that form a condition and return a Condition Object.
 *
 * @params left, operator and right strings
 * @return a pointer to a condition on heap - remember to delete!
 */
Condition * ConditionFactory::setCondition(string & left, string & c_operator, string & right) {
    const char * sign = c_operator.c_str();

    if (strcmp(LESS, sign) == 0) {
        return new ConditionLess(left, right);
    } else if (strcmp(LESS_OR_EQUAL, sign) == 0) {
        return new ConditionLE(left, right);
    } else if (strcmp(GREATER, sign) == 0) {
        return new ConditionGreater(left, right);
    } else if (strcmp(GREATER_OR_EQUAL, sign) == 0) {
        return new ConditionGE(left, right);
    } else if (strcmp(EQUAL, sign) == 0) {
        return new ConditionEqual(left, right);
    } else if (strcmp(NOT_EQUAL, sign) == 0) {
        return new ConditionNE(left, right);
    }

    throw "Condition operator not found";

}
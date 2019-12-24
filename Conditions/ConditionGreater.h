/**
 * Class for greater then condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#ifndef CONDITIONGREATER_H
#define CONDITIONGREATER_H

#include "Condition.h"

class ConditionGreater : public Condition {
    int isTrue();
    ConditionGreater(string left, string right) : Condition(left, right) {}
    ~ConditionGreater() = default;
};

#endif //CONDITIONGREATER_H

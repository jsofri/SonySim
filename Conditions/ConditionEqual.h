/**
 * Class for equal condition.
 *
 * @author Jhonny
 * @date 12.23.19
 */

#ifndef CONDITIONEQUAL_H
#define CONDITIONEQUAL_H

#include "Condition.h"

class ConditionEqual : public Condition {
    int isTrue();
    ConditionEqual(string left, string right) : Condition(left, right) {}
    ~ConditionEqual() = default;
};

#endif //CONDITIONEQUAL_H

/**
 * Class for less then condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#ifndef CONDITIONLESS_H
#define CONDITIONLESS_H

#include "Condition.h"

class ConditionLess : public Condition {
public:
    int isTrue() override;
    ConditionLess(string left, string right) : Condition(left, right) {}
    ~ConditionLess() = default;
};

#endif //CONDITIONLESS_H

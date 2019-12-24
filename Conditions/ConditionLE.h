/**
 * class for less then or equal condition.
 *
 * @author Jhonny
 * @date 12.23.19
 */

#ifndef CONDITIONLE_H
#define CONDITIONLE_H

#include "Condition.h"

class ConditionLE : public Condition {
public:
    int isTrue() override;
    ConditionLE(string left, string right) : Condition(left, right) {}
    ~ConditionLE() = default;
};

#endif //CONDITIONLE_H

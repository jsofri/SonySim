/**
 * class for greater then or equal condition.
 *
 * @author Jhonny
 * @date 12.23.19
 */

#ifndef CONDITIONGE_H
#define CONDITIONGE_H

#include "Condition.h"

class ConditionGE : public Condition {
public:
    int isTrue() override;
    ConditionGE(string left, string right) : Condition(left, right){};
    ~ConditionGE() = default;
};


#endif //CONDITIONGE_H

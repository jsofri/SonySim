/**
 * Class for not equal condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#ifndef CONDITIONNE_H
#define CONDITIONNE_H

#include "Condition.h"

class ConditionNE : public Condition {
    int isTrue();
    ConditionNE(string left, string right) : Condition(left, right) {}
    ~ConditionNE() = default;
};

#endif //CONDITIONNE_H

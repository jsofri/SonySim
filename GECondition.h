/**
 * greater or equal condition.
 *
 * @author Jhonny
 * @date 12.23.19
 */
#ifndef GECONDITION_H
#define GECONDITION_H

#include "Condition.h"

class GECondition : public Condition {
    int isTrue();
    GECondition(string left, string right) : left_string(left), right_string(right);
    ~GECondition() = default;
};


#endif //GECONDITION_H

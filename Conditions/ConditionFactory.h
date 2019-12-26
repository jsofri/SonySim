/**
 * Factory for making Condition Object.
 */

#ifndef CONDITIONFACTORY_H
#define CONDITIONFACTORY_H

#include "Condition.h"
#include "ConditionLess.h"
#include "ConditionLE.h"
#include "ConditionEqual.h"
#include "ConditionGreater.h"
#include "ConditionGE.h"
#include "ConditionNE.h"

#define LESS_OR_EQUAL "<="
#define GREATER_OR_EQUAL ">="
#define EQUAL "=="
#define NOT_EQUAL "!="
#define GREATER ">"
#define LESS "<"

class ConditionFactory {
public:
    Condition * setCondition(string &, string &, string &);
    ConditionFactory() = default;
    ~ConditionFactory() = default;
};


#endif //CONDITIONFACTORY_H

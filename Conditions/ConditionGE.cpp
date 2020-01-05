/**
 * class for greater then or equal condition.
 *
 * @author Jhonny
 * @date 12.23.19
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "ConditionGE.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is greater or equal right, else 0
 */
int ConditionGE::isTrue() {
    this -> calculateSides();

    return (this -> _left_value) >= (this -> _right_value);
}

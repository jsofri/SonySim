/**
 * Class for equal condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "ConditionEqual.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is equal to right, else 0
 */
int ConditionEqual::isTrue() {
    this -> calculateSides();

    return (this -> _left_value) == (this -> _right_value);
}

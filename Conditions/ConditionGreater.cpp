/**
 * Class for greater then condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "../DataManagement/GeneralData.h"
#include "../DataManagement/GlobalVars.h"
#include "ConditionGreater.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is greater then right, else 0
 */
int ConditionGreater::isTrue() {
    this -> calculateSides();

    return (this -> _left_value) > (this -> _right_value);
}

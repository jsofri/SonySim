/**
 * Class for less then or equal condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "ConditionLE.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is less then or equal to right, else 0
 */
int ConditionLE::isTrue() {
    this -> calculateSides();

    return (this -> _left_value) <= (this -> _right_value);
}

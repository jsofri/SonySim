/**
 * Class for not equal condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "../GeneralData.h"
#include "../GlobalVars.h"
#include "ConditionNE.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is not equal to right, else 0
 */
int ConditionNE::isTrue() {
    this -> calculateSides();

    return (this -> _left_value) != (this -> _right_value);
}

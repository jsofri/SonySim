/**
 * Class for less then condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "ConditionLess.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is less then right, else 0
 */
int ConditionLess::isTrue() {
    this -> calculateSides();

    return (this -> _left_value) < (this -> _right_value);
}

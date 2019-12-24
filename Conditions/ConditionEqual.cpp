/**
 * Class for equal condition.
 *
 * @author Jhonny
 * @date 12.24.19
 */

#include "ConditionEqual.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is equal to right, else 0
 */
int ConditionEqual::isTrue() {
    this -> calculateSides();

    return (this -> left_value) == (this -> right_value);
}

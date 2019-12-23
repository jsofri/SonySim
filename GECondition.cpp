/**
 * greater or equal condition.
 *
 * @author Jhonny
 * @date 12.23.19
 */

#include "GECondition.h"

int GECondition::isTrue() {
    this -> calculateSides();

    return (this -> left_value) <= (this -> right_value);
}
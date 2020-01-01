/**
 * Abstract class of binary arithmetic expression.
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */

#ifndef BINARYOPERATOR_H_
#define BINARYOPERATOR_H_

#include "Expression.h"
#include "Value.h"
#include <string>

class BinaryOperator : public Expression {
 protected:
  Expression* left_;
  Expression* right_;
};

#endif //BINARYOPERATOR_H_

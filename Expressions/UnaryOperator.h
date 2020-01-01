/**
 * an unary expression is an arithmetic operation that consist of one inner expression.
 * therefore implements from Expression.
 * @author Yehonatan Sofri
 * @date 03/11/2019
 */

#ifndef UNARYOPERATOR_H_
#define UNARYOPERATOR_H_

#include "Expression.h"
#include "Value.h"

class UnaryOperator : public Expression  {
 protected:
  Expression* expression_;
};

#endif //UNARYOPERATOR_H_

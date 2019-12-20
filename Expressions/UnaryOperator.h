
// Created by jhonny on 03/11/2019.//
//

#ifndef EX1__UNARYOPERATOR_H_
#define EX1__UNARYOPERATOR_H_

#include "Expression.h"
#include "Value.h"

class UnaryOperator : public Expression  {
 protected:
  Expression* expression_;
};

#endif //EX1__UNARYOPERATOR_H_

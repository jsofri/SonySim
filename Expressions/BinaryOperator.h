//
// Created by jhonny on 09/11/2019.
//

#ifndef EX1__BINARYOPERATOR_H_
#define EX1__BINARYOPERATOR_H_

#include "Expression.h"
#include "Value.h"
#include <string>

class BinaryOperator : public Expression {
 protected:
  Expression* left_;
  Expression* right_;
};

#endif //EX1__BINARYOPERATOR_H_

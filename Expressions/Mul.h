//
// Created by jhonny on 09/11/2019.
//

#ifndef EX1__MUL_H_
#define EX1__MUL_H_

#include "BinaryOperator.h"

class Mul : public BinaryOperator {
 public:
  Mul(Expression*, Expression*);
  double calculate() override;
  ~Mul() override;
};

#endif //EX1__MUL_H_

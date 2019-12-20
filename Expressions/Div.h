//
// Created by jhonny on 09/11/2019.
//

#ifndef EX1__DIV_H_
#define EX1__DIV_H_

#include "BinaryOperator.h"

class Div : public BinaryOperator {
 public:
  Div(Expression*, Expression*);
  double calculate() override;
  ~Div() override;
};

#endif //EX1__DIV_H_

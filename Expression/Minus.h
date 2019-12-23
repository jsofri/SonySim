//
// Created by jhonny on 09/11/2019.
//

#ifndef EX1__MINUS_H_
#define EX1__MINUS_H_
#include "BinaryOperator.h"

class Minus : public BinaryOperator {
 public:
  Minus(Expression*, Expression*);
  double calculate() override;
  ~Minus() override;
};

#endif //EX1__MINUS_H_

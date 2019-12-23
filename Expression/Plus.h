//
// Created by jhonny on 09/11/2019.
//

#ifndef EX1__PLUS_H_
#define EX1__PLUS_H_
#include "BinaryOperator.h"

class Plus : public BinaryOperator{
 public:
  Plus(Expression*, Expression*);
  double calculate() override;
  ~Plus() override;
};

#endif //EX1__PLUS_H_

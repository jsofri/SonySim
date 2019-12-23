//
// Created by jhonny on 06/11/2019.
//

#ifndef EX1__VALUE_H_
#define EX1__VALUE_H_

#include "Expression.h"

class Value: public Expression {
 public:
  Value(double number) : value_(number) {}
  double calculate() override;
  ~Value() override = default;
 private:
  double value_;
};

#endif //EX1__VALUE_H_

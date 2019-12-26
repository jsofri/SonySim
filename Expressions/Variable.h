//
// Created by jhonny on 06/11/2019.
//

#ifndef EX1__VARIABLE_H_
#define EX1__VARIABLE_H_

#include "Expression.h"
#include "stdio.h"
#include <iostream>
#include <string>

class Variable : public Expression {
 public:
  Variable(string, double);
  Variable& operator++();
  Variable& operator++(int);
  Variable& operator--();
  Variable& operator--(int);
  Variable& operator+=(double);
  Variable& operator-=(double);
  double calculate() override;
  static bool NameIsValid(string);
  ~Variable() override = default;
 private:
  string name_;
  double value_;
};

#endif //EX1__VARIABLE_H_
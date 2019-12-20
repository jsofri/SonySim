//
// Created by jhonny on 09/11/2019.
//

#include "Mul.h"

Mul::Mul(Expression *new_left, Expression *new_right) {
  this -> left_ = new_left;
  this -> right_ = new_right;
}

double Mul::calculate() {
  double exp_left = this -> left_ -> calculate();
  double exp_right = this -> right_ -> calculate();

  return exp_left * exp_right;
}

Mul::~Mul() {
  delete(this -> left_);
  delete(this -> right_);
}


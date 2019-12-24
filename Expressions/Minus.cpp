//
// Created by jhonny on 09/11/2019.
//

#include "Minus.h"

Minus::Minus(Expression *new_left, Expression *new_right) {
  this -> left_ = new_left;
  this -> right_ = new_right;
}

double Minus::calculate() {
  double exp_left = this -> left_ -> calculate();
  double exp_right = this -> right_ -> calculate();

  return exp_left - exp_right;
}

Minus::~Minus() {
  delete(this -> left_);
  delete(this -> right_);
}

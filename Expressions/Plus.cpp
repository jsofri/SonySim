//
// Created by jhonny on 09/11/2019.
//

#include "Plus.h"

Plus::Plus(Expression *newLeft, Expression *newRight) {
  this -> left_ = newLeft;
  this -> right_ = newRight;
}

double Plus::calculate() {
  double exp_left = this -> left_ -> calculate();
  double exp_right = this -> right_ -> calculate();

  return exp_left + exp_right;
}

Plus::~Plus() {
  delete(this -> left_);
  delete(this -> right_);
}

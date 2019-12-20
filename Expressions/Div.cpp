//
// Created by jhonny on 09/11/2019.
//

#include "Div.h"

Div::Div(Expression *new_left, Expression *new_right) {
  this -> left_ = new_left;
  this -> right_ = new_right;
}

double Div::calculate() {
  double exp_left = this -> left_ -> calculate();
  double exp_right = this -> right_ -> calculate();

  if (exp_right == 0.0) {
    throw "Division by 0 is invalid";

    return 0;
  }

  return exp_left / exp_right;
}

Div::~Div() {
  delete(this -> left_);
  delete(this -> right_);
}

//
// Created by jhonny on 06/11/2019.
//

#include "UMinus.h"

#include "Value.h"

UMinus::UMinus(Expression* expression1) {
  this -> expression_ = expression1;
}

double UMinus::calculate() {
  return -(this -> expression_ -> calculate());
}

UMinus::~UMinus() {
  delete(this -> expression_);
}
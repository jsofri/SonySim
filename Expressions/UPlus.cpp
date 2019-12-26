//
// Created by jhonny on 03/11/2019.
//

#include "UPlus.h"

UPlus::UPlus(Expression* expression_1) {
  this -> expression_ = expression_1;
}

double UPlus::calculate() {
  return this -> expression_ -> calculate();
}

UPlus::~UPlus() {
  delete(this -> expression_);
}
  
/**
 * an unary expression, do nothing to the value.
 * methods are trivial.
 *
 * @author Yehonatan Sofri
 * @date 03/11/2019
 */

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

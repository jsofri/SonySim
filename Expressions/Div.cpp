/**
 * Class for handling a division between Expressions.
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */

#include "Div.h"

/**
 * Constructor.
 *
 * @param left and right expressions - we divide left by right.
 */
Div::Div(Expression *new_left, Expression *new_right) {
  this -> left_ = new_left;
  this -> right_ = new_right;
}

/**
 * calculate expression - get result.
 *
 * @return value of expression (double)
double Div::calculate() {
  double exp_left = this -> left_ -> calculate();
  double exp_right = this -> right_ -> calculate();

  if (exp_right == 0.0) {
    throw "Division by 0 is invalid";

    return 0;
  }

  return exp_left / exp_right;
}

/**
 * Dtor.
 */
Div::~Div() {
  delete(this -> left_);
  delete(this -> right_);
}

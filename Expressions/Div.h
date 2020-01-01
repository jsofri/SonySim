/**
 * Header of class Div - represent division between expressions.
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */ 

#ifndef DIV_H_
#define DIV_H_

#include "BinaryOperator.h"

class Div : public BinaryOperator {
 public:
  Div(Expression*, Expression*);
  double calculate() override;
  ~Div() override;
};

#endif //DIV_H_

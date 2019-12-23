//
// Created by jhonny on 06/11/2019.
//

#ifndef EX1__UMINUS_H_
#define EX1__UMINUS_H_

#include "UnaryOperator.h"

class UMinus : public UnaryOperator {
 public:
  UMinus(Expression*);
  double calculate() override;
  ~UMinus() override;
};

#endif //EX1__UMINUS_H_

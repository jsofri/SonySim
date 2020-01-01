/**
 * a binary expression, make substraction.
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */

#ifndef MUL_H_
#define MUL_H_

#include "BinaryOperator.h"

class Mul : public BinaryOperator {
 public:
  Mul(Expression*, Expression*);
  double calculate() override;
  ~Mul() override;
};

#endif //MUL_H_

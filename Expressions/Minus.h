/**
 * Class minus - a binary expression, make substraction.
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */

#ifndef MINUS_H_
#define MINUS_H_
#include "BinaryOperator.h"

class Minus : public BinaryOperator {
 public:
  Minus(Expression*, Expression*);
  double calculate() override;
  ~Minus() override;
};

#endif //MINUS_H_

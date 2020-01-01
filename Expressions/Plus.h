/**
 * Class minus - a binary expression, make addition.
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */

#ifndef PLUS_H_
#define PLUS_H_
#include "BinaryOperator.h"

class Plus : public BinaryOperator{
 public:
  Plus(Expression*, Expression*);
  double calculate() override;
  ~Plus() override;
};

#endif //PLUS_H_

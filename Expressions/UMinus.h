/**
 * an unary expression, negation of value.
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */

#ifndef UMINUS_H_
#define UMINUS_H_

#include "UnaryOperator.h"

class UMinus : public UnaryOperator {
 public:
  UMinus(Expression*);
  double calculate() override;
  ~UMinus() override;
};

#endif //UMINUS_H_

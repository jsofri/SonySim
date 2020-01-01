/**
 * an unary expression, hold a value.
 *
 * @author Yehonatan Sofri
 * @date 06/11/2019
 */

#ifndef VALUE_H_
#define VALUE_H_

#include "Expression.h"

class Value: public Expression {
 public:
  Value(double number) : value_(number) {}
  double calculate() override;
  ~Value() override = default;
 private:
  double value_;
};

#endif //VALUE_H_

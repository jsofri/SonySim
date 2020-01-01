/**
 * an unary expression, doesn't do anything to value.
 *
 * @author Yehonatan Sofri
 * @date 03/11/2019
 */

#ifndef UPLUS_H_
#define UPLUS_H_

#include "UnaryOperator.h"

class UPlus : public UnaryOperator {
  public:
    UPlus(double number);
    UPlus(Expression & expression);
    UPlus(Expression* expression);
    double calculate() override;
    ~UPlus() override;
};

#endif //UPLUS_H_

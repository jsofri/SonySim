//
// Created by jhonny on 03/11/2019.
//

#ifndef EX1__UPLUS_H_
#define EX1__UPLUS_H_

#include "UnaryOperator.h"

class UPlus : public UnaryOperator {
  public:
    UPlus(double number);
    UPlus(Expression & expression);
    UPlus(Expression* expression);
    double calculate() override;
    ~UPlus() override;
};

#endif //EX1__UPLUS_H_

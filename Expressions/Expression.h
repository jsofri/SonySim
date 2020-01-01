/**
 * Interface for arithmetic expression.
 * each expression can be evaluated (do that by calculate()).
 *
 * @author Yehonatan Sofri
 */
#ifndef EXPRESSION_H
#define EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //EXPRESSION_H

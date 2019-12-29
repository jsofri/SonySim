/**
 * abstract class for handling conditions in the code.
 * all inheriting classes will be called ConditionXXX.
 * where XXX is the condition (equal, LE, LE, etc..).
 *
 * @author Jhonny
 * @date 12.23.19
 */

#ifndef CONDITION_H
#define CONDITION_H

class Condition {
public:
    virtual int isTrue() = 0;
    void calculateSides();
    float calculate(string &);
    Condition(string left, string right) : _left_string(left), _right_string(right) {};
    ~Condition() = default;
protected:
    string _left_string;
    string _right_string;
    float _left_value;
    float _right_value;
};
#endif //CONDITION_H
/**
 * class is a generic object for all uses in program.
 * get a string and return a float - the value that the string represent.
 *
 * @author Yehonatan Sofri
 * @date 24.12.19
 */

#ifndef FLOATFROMSTRING_H
#define FLOATFROMSTRING_H

#include "GeneralData.h"

#define NUMBERS "1234567890."
#define ABC "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwhyz_0123456789"

class FloatFromString {
public:
    float calculateString(string);
    FloatFromString() = default;
    ~FloatFromString() = default();
private:
    float  floatFromExpression(string &);
    void   setVariables(Interpreter * &, string);
    string delSpaces(string &str);
    bool   isVar(string &);
    bool   isNumber(string &);
    bool   isExpression(string &);
};

#endif //FLOATFROMSTRING_H

/**
 * class is a generic object for all uses in program.
 * get a string and return a float - the value that the string represent.
 *
 * @author Yehonatan Sofri
 * @date 24.12.19
 */

#ifndef FLOATFROMSTRING_H
#define FLOATFROMSTRING_H

#include "Expressions/Interpreter.h"

#define NUMBERS "1234567890."
#define ABC "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwhyz_0123456789"

using namespace std;

class FloatFromString {
public:
    static float calculateString(string);
    FloatFromString() = default;
    ~FloatFromString() = default;
private:
    static float  floatFromExpression(string &);
    static void   setVariables(Interpreter * &, string);
    static string delSpaces(string &str);
    static bool   isVar(string &);
    static bool   isNumber(string &);
    static bool   isExpression(string &);
};

#endif //FLOATFROMSTRING_H

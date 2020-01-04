/**
 * This class is responsible for getting a string and returning a float - the value that the string represent.
 * The string can be either a number, a veriable or an expression.
 *
 * @author Yehonatan Sofri
 * @date 24.12.19
 */

#ifndef FLOATFROMSTRING_H
#define FLOATFROMSTRING_H

#include "Expressions/Interpreter.h"

#define NUMBERS "1234567890.-"
#define ABC "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_0123456789"

using namespace std;

class FloatFromString {
public:
    /**
     * get a string and return the number it represents.
     *
     * @param str string that can be calculated to a number.
     * @return value in the string.
     */
    static float calculateString(string);
    
    /**
     * Constructor
     */
    FloatFromString() = default;
    
    /**
     * Destructor
     */
    ~FloatFromString() = default;
    
private:
    /**
     * get a string of arithmetic Expression and returns it's value.
     * @param str expression string
     * @return the float value of the expression
     */
    static float  floatFromExpression(string &);
    
    /**
     * Extracts the variables names from the string and assigns to each the relevant value from symbol_table.
     *
     * @param interpreter Interpreter reference
     * @param str string that represents an arithmetic expression
     */
    static void   setVariables(Interpreter * &, string);
    
    /**
     * remove spaces from string.
     *
     * @param str reference to a string
     * @return string withour spaces
     */
    static string delSpaces(string &str);
    
    /**
     * check if given string is a variable, by elimination.
     *
     * @param str string of a token
     * @return boolean - true or false
     */
    static bool   isVar(string &);
    
    /**
     * check if a given string is a float number.
     *
     * @test 12.16.19 by YS
     * @param str reference to a string.
     * @return bool - 1 if true, 0 if false
     */
    static bool   isNumber(string &);
    
    /**
     * check if a given string is an expression by finding operators.
     * not perfect - assuming you went through isNumber beforehand.
     *
     * @test 12.16.19 by YS
     * @param str reference to a string.
     * @return bool - 1 if true, 0 if false
     */
    static bool   isExpression(string &);
};

#endif //FLOATFROMSTRING_H

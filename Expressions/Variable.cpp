/**
 * a variable is a representation of number using a name
 *
 * @author Yehonatan Sofri
 * @date 09/11/2019
 */

#include "Variable.h"

using namespace std;

Variable::Variable(string name_1, double value_1) {

  if (!NameIsValid(name_1)){

    cerr<<"Invalid Variable name"<<endl;
  }

  this -> name_ = name_1;
  this -> value_ = value_1;
}

Variable& Variable::operator++() {
  this -> value_ += 1;

  return *this;
}

Variable& Variable::operator++(int) {
  return operator++();
}

Variable& Variable::operator--() {
  this -> value_ -= 1;

  return *this;
}

Variable& Variable::operator--(int) {
  return operator--();
}

Variable& Variable::operator+=(double number) {
  this -> value_ += number;

  return *this;
}

Variable& Variable::operator-=(double number) {
  this -> value_ -= number;

  return *this;
}

double Variable::calculate() {
  return this -> value_;
}

bool Variable::NameIsValid(string str) {

  //if first char in string is a number
  if (str[0] <= 57 && str[0] >= 48) {
    return false;
  }

  if (str.length() > 1) {
    //if one of the next chars is not an underscore, number or a letter
    for (int i = 1, c = str[i]; c != 0; c = str[++i]) {

      // 0-9 = [48, 57], A-Z = [65, 90], a-z = [97,122], _ = 95
      if (!(((c <= 57) && (c >= 48)) || ((c >= 65) && (c <= 90)) || ((c >= 97) || (c<=122)) || (c==95))) {
        return false;
      }
    }
  }

  return true;
}

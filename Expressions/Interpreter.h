//
// Created by jhonny on 09/11/2019.
//

#ifndef EX1__INTERPRETER_H_
#define EX1__INTERPRETER_H_


#include "Expression.h"
#include "Variable.h"
#include "Mul.h"
#include "UMinus.h"
#include "Div.h"
#include "UPlus.h"
#include "Value.h"
#include "Plus.h"
#include "Minus.h"
#include <string>
#include <regex>
#include <stack>
#include <queue>
#include <string>

class Interpreter {
 public:
  Expression*  interpret(string);
  void         setVariables(const char *);
  void         SetVariable(string);
  void         setVariable(string, double);
  regex        getRegexOfTokens();
  void         CheckString(string);
  bool         CheckOperator(char);
  void         CountBrackets(string);
  char*        Simplify(string);
  void         CheckExpressionInput(string);
  bool         CheckVariableNameInput(string input);
  bool         CheckVariableValueInput(string input);
  void         SetQueue(string);
  bool         IsOperator(string);
  Expression*  SetExpressionFromQueue();
  void         HandleToken(string);
  void         HandleOperator(char);
  int          GetPrecedence(string);
  void         MoveOneFromStackToQueue();
  ~Interpreter();
 private:
  map<string, double> variables_;
  stack<string>       string_stack_;
  queue<string>       string_queue_;
};

#endif //EX1__INTERPRETER_H_

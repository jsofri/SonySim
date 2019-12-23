/**
 *
 */

#include "Interpreter.h"

//get a const char * (input from user) and make Variable of it
void Interpreter::setVariables(const char* chars) {
  string intermediate, str = chars;

  //stream is needed to split string
  stringstream strstrm(str);

  if (str.empty()) {
    throw "empty string was sent to setVariables";
  }

  // Tokenizing w.r.t. delimiter ';'
  while(getline(strstrm, intermediate, ';'))
  {
    if (!intermediate.empty()) {
      SetVariable(intermediate);
    }
  }
}

//get a string "kuki=3.2" and set a Variable "kuki" with the value of 3.2
void Interpreter::SetVariable(string str) {
  int                  delimiter_position;
  double               value;
  string               name;
  string               value_string;

  delimiter_position = str.find("=");

  if (delimiter_position == -1) {
    throw "invalid input";
  }

  //make name string
  name = str.substr(0, delimiter_position);

  //make value string
  value_string = str.substr(delimiter_position + 1, str.length());

  if (this -> CheckVariableNameInput(name)
        && this -> CheckVariableValueInput(value_string)) {
    value = stod(value_string); //string->double

    this -> setVariable(name, value);
  }
  else {
    throw "invalid input";
  }
}

void Interpreter::setVariable(string name, double value) {
    pair<string, double> key_value_pair;

    if (!(this -> variables_.find(name) == this -> variables_.end())) {
        this -> variables_.erase (name);
    }

    key_value_pair = make_pair(name, value);

    this -> variables_.insert(key_value_pair);
}

Expression* Interpreter::interpret(string raw_string) {
  char* fixed;

  this -> CheckString(raw_string);
  fixed = Simplify(raw_string);
  this -> SetQueue(fixed);
  delete(fixed);  
  return this -> SetExpressionFromQueue();
}

void Interpreter::CheckString(string raw_string) {

    this -> CountBrackets(raw_string);

    for (int i = 0, len = raw_string.length(); i < len; i++) {
      if (this -> CheckOperator(raw_string[i])
            && this -> CheckOperator(raw_string[i + 1])) {
        throw "Double operator detected in string";
      }
    }


}

char* Interpreter::Simplify(string input) {
  char *copy = new char[input.length() + 1];

  this -> CheckExpressionInput(input);

  strcpy(copy, input.c_str());

  for (unsigned int i = 0; i < input.length(); i++) {
    if ((input[i] == '-') || (input[i] == '+')) {
      if ((i == 0) || (input[i - 1] == '(')) {
        if (input[i] == '-') {
          copy[i] = '!';
        } else {
          copy[i] = '#';
        }
      }
    }
  }

  return copy;
}

void Interpreter::CheckExpressionInput(string input) {
  int tmp, len = input.length();

  for (int i = 0; i < len; i++) {
    tmp = input[i];

    //check that the characters are valid
    if ((tmp > 122) || (tmp < 40) || (tmp == 44) || ((tmp < 65) && (tmp > 57))
          || ((tmp < 95) && (tmp > 90)) || (tmp == 96)) {
      throw "invalid input for interpret()";
    }
  }
}

bool Interpreter::CheckVariableNameInput(string input) {
  string rest_chars = input.substr(1);

  //input doesn't start with a letter
  if (!(((input[0] >= 97) && (input[0] <= 122)) || ((input[0] <= 90) && (input[0] >= 65)))) {
    return false;
  }

  for (int i = 0, c = rest_chars[i]; c != 0; c = rest_chars[++i]) {

    //check that each letter is [_A-Za-z0-9]
    if (!((c == 95) || ((c >= 48) && (c <= 57)) || ((c >= 65) && (c <= 90))
          || ((c >= 97) && (c <= 122)))) {
      return false;
    }
  }

  return true;
}

bool Interpreter::CheckVariableValueInput(string input) {
  try {
    stod(input);

  } catch (exception exp) {
    return false;
  }

  return true;
}

//get an infix string and make a queue of postfix expression
void Interpreter::SetQueue(string infix) {

  regex rgx = this -> getRegexOfTokens();

  std::regex_iterator<std::string::iterator> rit (infix.begin(), infix.end(), rgx);
  std::regex_iterator<std::string::iterator> rend;

  while (rit!=rend) {

    this -> HandleToken(rit->str());

    ++rit;
  }

  while(!this -> string_stack_.empty()) {
    this -> MoveOneFromStackToQueue();
  }
}

//regex catch doubles, variables and operators
regex Interpreter::getRegexOfTokens() {
    regex rgx("[a-zA-z_][a-zA-z_\\d]*|[\\d]+[.]?[\\d]+|[\\d]+|[!-_+#/*()]");

    return rgx;
}

void Interpreter::HandleToken(string str) {
  if (this -> IsOperator(str)) {
    if(string_stack_.empty()) {
      string_stack_.push(str);
    }
    else {
      this->HandleOperator(str[0]);
    }
  }
  else { //str is a number
    this -> string_queue_.push(str);
  }
}

bool Interpreter::CheckOperator(char c) {
  switch (c) {
    case ('*'):
    case ('+'):
    case ('-'):
    case ('/'):return true;
  }

  return false;
}

void Interpreter::CountBrackets(string raw_string) {
  int left = 0, right = 0;

  for (int i = 0, len = raw_string.length(); i <= len; i++) {
    if (raw_string[i] == '(') {
      left++;
    }
    else if (raw_string[i] == ')') {
      right++;
    }
  }

  if (left != right) {
    throw "Uneven Number of Brackets";
  }
}

bool Interpreter::IsOperator(string str) {

  if (str.length() == 1) {

    char c = str[0];
    switch (c) {
      case ('!'):             //UMinus
      case ('#'):             //UPlus
      case ('('):
      case (')'):
      case ('*'):
      case ('+'):
      case ('-'):
      case ('/'):return true;
    }
  }
  return false;
}
 void Interpreter::HandleOperator(char oprtor) {
  string s;

  if (oprtor == ')') {
    if (string_stack_.top()[0] != '(') {

      do {
        this->MoveOneFromStackToQueue();
      } while (this->string_stack_.top()[0] != '(');
    }

    this->string_stack_.pop(); //remove '(' from stack
  }
  else if (oprtor == '(') {
    s = string(1, oprtor);
    this -> string_stack_.push(s);
  }
  else { //arithmetic operator
    int precedence;
    int top = this -> GetPrecedence(string_stack_.top());

    s = string(1, oprtor);
    precedence = this -> GetPrecedence(s);

    if (precedence <= top) {

      do {
        this->MoveOneFromStackToQueue();

        if (this->string_stack_.empty()) {
          break;
        }

        top = GetPrecedence(this->string_stack_.top());
      } while (top > precedence);
    }

    this -> string_stack_.push(s);
  }
}

void Interpreter::MoveOneFromStackToQueue() {
  string tmp = this->string_stack_.top();
  this->string_stack_.pop();
  this -> string_queue_.push(tmp);
}

Expression* Interpreter::SetExpressionFromQueue() {
  stack<Expression*> expression_stack;
  Expression*        expression;
  Expression*        left;
  Expression*        right;
  string             str;
  double             number;


  while(!this->string_queue_.empty()) {

    str = this->string_queue_.front();
    this->string_queue_.pop();

    if(this->IsOperator(str)) {
      right = expression_stack.top();
      expression_stack.pop();

      if (str[0] == '!') {    //UMinus
        expression = new UMinus(right);
      }
      else if (str[0] =='#') { //UPlus
        expression = new UPlus(right);
      }
      else {                   //binaryOperator
        left = expression_stack.top();
        expression_stack.pop();

        switch(str[0]) {
          case('-'): {
            expression = new Minus(left, right);
            break;
          }
          case ('+'): {
            expression = new Plus(left, right);
            break;
          }
          case('/'): {
            expression = new Div(left, right);
            break;
          }
          case('*'): {
            expression = new Mul(left, right);
            break;
          }
          default: throw "unrecognized operator";
        }
      }
    }
    else { //it's a double/ variable
      if ((str[0] >= 48) && (str[0] <= 57)) {
        number = stod(str);
        expression = new Value(number);
      }
      else {
        if (this->variables_.find(str) == this->variables_.end()) {
          throw "variable does not exist error";
        }
        else {
          number = this->variables_[str];
          expression = new Variable(str, number);
        }
      }
    }

    expression_stack.push(expression);
  }

  return expression_stack.top();
}

int Interpreter::GetPrecedence(string oprtor) {

  switch (oprtor[0]) {
    case ('!'):
    case ('#'): return 3;
    case ('*'):
    case ('/'): return 2;
    case ('+'):
    case ('-'): return 1;
    case ('('):
    case (')'): return 0;
    default: throw "unrecognized operator";
  }
}

Interpreter::~Interpreter() {
}

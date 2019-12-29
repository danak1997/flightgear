//
// Created by chen96 on 28/12/2019.
//

#include "ExpressionCalculate.h"
#include "Expression.h"
#include "Maps.h"
#include <queue>
#include <stack>
#include <regex>
#include <map>
#include <stdexcept>
#include <exception>

// Value class
Value::Value(double val1) : val(val1) {}
double Value::calculate() {
  return val;
}
Value::~Value() = default;

// BinaryOperator class
BinaryOperator::BinaryOperator(Expression *left1, Expression *right1) {
  left = left1;
  right = right1;
}
BinaryOperator::~BinaryOperator() {
  delete left;
  delete right;
}

// UnaryOperator class
UnaryOperator::UnaryOperator(Expression *exp1) {
  exp = exp1;
}
UnaryOperator::~UnaryOperator() {
  delete exp;
}

// Variable class
Variable::Variable(string name1, double value1) {
  name = name1;
  value = value1;
}
Variable &Variable::operator++(int num) {
  value++;
  return *this;
}
Variable &Variable::operator--(int num) {
  value--;
  return *this;
}
Variable &Variable::operator++() {
  value++;
  return *this;
}
Variable &Variable::operator--() {
  value--;
  return *this;
}
Variable &Variable::operator+=(double num) {
  value += num;
  return *this;
}
Variable &Variable::operator-=(double num) {
  value -= num;
  return *this;
}
double Variable::calculate() {
  return value;
}
Variable::~Variable() = default;

// Plus class
Plus::Plus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}
double Plus::calculate() {
  return left->calculate() + right->calculate();
}
Plus::~Plus() = default;

// Minus class
Minus::Minus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}
double Minus::calculate() {
  return left->calculate() - right->calculate();
}
Minus::~Minus() = default;

// Mul class
Mul::Mul(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}
double Mul::calculate() {
  return left->calculate() * right->calculate();
}
Mul::~Mul() = default;

// Div class
Div::Div(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}
double Div::calculate() {
  if (right->calculate() == 0) {
    throw "Division by zero";
  }
  return left->calculate() / right->calculate();
}
Div::~Div() = default;

// UPlus class (Unary plus)
UPlus::UPlus(Expression *exp1) : UnaryOperator(exp1) {}
double UPlus::calculate() {
  return exp->calculate();
}
UPlus::~UPlus() = default;

// UMinus class (Unary minus)
UMinus::UMinus(Expression *exp1) : UnaryOperator(exp1) {

  exp = new Mul(new Value(-1.0), exp1);
}
double UMinus::calculate() {
  return exp->calculate();
}
UMinus::~UMinus() = default;

// Interpreter class
Interpreter::Interpreter() {
  precedence["+"] = 1;
  precedence["-"] = 1;
  precedence["*"] = 2;
  precedence["/"] = 2;
  precedence["("] = 3;
  precedence[")"] = 3;
  precedence["!-!"] = 4;
  precedence["!+!"] = 4;
}
// gets the precedence of an operator from the precedence map
int Interpreter::getOpPrecedence(string op) {
  return precedence[op];
}
// The interpret function creates an expression from a string, using Shunting-yard algorithm
Expression *Interpreter::interpret(string str) {
  queue<string> output;
  stack<string> operators;
  // iterates over the given string
  int iterator = 0;
  smatch numsAndVarsMatch;
  int countNumsAndVars = 0;
  int pos = 0;
  // checks if the string is an invalid expression
  if ((!checkValidNumOp(str)) || (!checkParentheses(str)) || (!checkValidOrder(str))) {
    throw "Invalid expression";
  }
  smatch unaryMinus;
  regex findUnaryM("(^(\\-)|(\\(-))");
  // the number of unary minus
  int numMinus = 0;
  // counts the number of unary minus in the string
  numMinus = distance(
      sregex_iterator(str.begin(), str.end(), findUnaryM),
      sregex_iterator());
  int *positionsM = new int[numMinus];
  if (positionsM == nullptr) {
    throw "Error: memory could not be allocated";
  }
  int numPosition = 0;
  int itrStr = 0;
  // the loop adds to the position array - the positions of the unary minus in the string
  for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), findUnaryM); it != sregex_iterator(); it++) {
    unaryMinus = *it;
    positionsM[numPosition] = unaryMinus.position();
    numPosition++;
  }
  // replacing the unary minus to "!-!"
  for (int i = 0; i < numMinus; i++) {
    if ((positionsM[i] == 0) && (str[0] == '-')) {
      str.replace(positionsM[i], 1, "!-!");
      itrStr++;
    } else {
      str.replace(positionsM[i] + 2 * itrStr + 1, 1, "!-!");
      itrStr++;
    }
  }
  delete[] positionsM;
  smatch unaryPlus;
  regex findUnaryP(R"(((^\+)|(\(\+)))");
  // the number of unary plus
  int numPlus = 0;
  // counts the number of unary plus in the string
  numPlus = distance(
      sregex_iterator(str.begin(), str.end(), findUnaryP),
      sregex_iterator());
  int *positionsP = new int[numPlus];
  if (positionsP == nullptr) {
    throw "Error: memory could not be allocated";
  }
  numPosition = 0;
  itrStr = 0;
  // the loop adds to the position array - the positions of the unary plus in the string
  for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), findUnaryP); it != sregex_iterator(); it++) {
    unaryPlus = *it;
    positionsP[numPosition] = unaryPlus.position();
    numPosition++;
  }
  // replacing the unary plus to "!+!"
  for (int i = 0; i < numPlus; i++) {
    if (positionsP[i] == 0) {
      str.replace(positionsP[i], 1, "!+!");
      itrStr++;
    } else {
      str.replace(positionsP[i] + 2 * itrStr + 1, 1, "!+!");
      itrStr++;
    }
  }
  delete[] positionsP;
  // checks if the string is an invalid expression
  if (!checkVarAndP(str)) {
    throw "Invalid Expression";
  }
  regex findNumsAndVars(R"([^(\-|\(|\)|\+|\*|\/|\!)]+)");
  sregex_iterator it = sregex_iterator(str.begin(), str.end(), findNumsAndVars);
  // counts the number of numbers and variables in the string
  countNumsAndVars = distance(
      sregex_iterator(str.begin(), str.end(), findNumsAndVars),
      sregex_iterator());
  // An array that contains variables and numbers even if they are invalid
  string variablesAndNums[countNumsAndVars];
  for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), findNumsAndVars); it != sregex_iterator(); it++) {
    numsAndVarsMatch = *it;
    variablesAndNums[pos] = numsAndVarsMatch.str();
    pos++;
  }
  pos = 0;
  // iterating the string
  while (iterator < str.length()) {
    // the current char
    char sign = str[iterator];
    string strSign(1, sign);
    // checks if the string is an operator
    if (checkIfOp(strSign)) {
        while ((!operators.empty())&& ((precedence[operators.top()] >= precedence[strSign]) && (operators.top().compare("(") != 0))) {
          output.push(operators.top());
          operators.pop();
        }

      operators.push(strSign);
      iterator++;
    } else if (strSign.compare("(") == 0) {
      operators.push(strSign);
      iterator++;
    } else if (strSign.compare(")") == 0) {
      if (!operators.empty()) {
        // removes all the operators from stack until it gets to "("
        while ((!operators.empty()) && (operators.top().compare("(") != 0)) {
          output.push(operators.top());
          operators.pop();
        }
      } else {
        throw "Mismatched parentheses";
      }
      if (!operators.empty()) {
        if (operators.top().compare("(") == 0) {
          operators.pop();
        }
      } else {
        throw "Mismatched parentheses";
      }
      iterator++;
      // checks if it an unary minus/plus (starts with "!")
    } else if (strSign.compare("!") == 0) {
      string subUnary = str.substr(iterator, 3);
      if ((subUnary.compare("!-!") == 0) || (subUnary.compare("!+!") == 0)) {
        operators.push(subUnary);
        iterator += 3;
      }
    } else {
      // checks if there are variables or numbers in the string
      if (countNumsAndVars == 0) {
        throw "The Expression does not contain numbers or variables";
      } else {
        // checks if the string is a number
        if (checkIfNum(variablesAndNums[pos])) {
          output.push(variablesAndNums[pos]);
          iterator += variablesAndNums[pos].length();
          pos++;
          // checks if the string is a variable
        } else if (checkIfVariable(variablesAndNums[pos])) {
          output.push(variablesAndNums[pos]);
          iterator += variablesAndNums[pos].length();
          pos++;
        } else {
          throw "The Expression contains invalid numbers or variables";
        }
      }
    }
  }
  while (!operators.empty()) {
    // checks if there are parenthesis left in the stack
    if ((operators.top().compare("(") == 0) || ((operators.top().compare(")") == 0))) {
      throw "Mismatched parentheses";
    }
    output.push(operators.top());
    operators.pop();
  }
  return postfixToExp(output);
}

// The function adds variables and their values to the interpreter's map
void Interpreter::setVariables(string s) {
  smatch sVars;
  regex split("[^;]+");
  int count = 0;
  // the number of assignments in the string
  count = distance(
      sregex_iterator(s.begin(), s.end(), split),
      sregex_iterator());
  string *vars = new string[count];
  if (vars == nullptr) {
    throw "Error: memory could not be allocated";
  }
  int counter = 0;
  // copy the assignments to vars array
  for (sregex_iterator it = sregex_iterator(s.begin(), s.end(), split); it != sregex_iterator(); it++) {
    sVars = *it;
    vars[counter] = sVars.str();
    counter++;
  }
  regex eqSplit("[^=]+");
  smatch splitMatch;
  string eq[2];
  // goes over the vars array
  for (int i = 0; i < count; i++) {
    int pos = 0;
    // checks if the equation is valid
    if (checkValidEquation(vars[i])) {
      // copy the var and value to the eq array
      for (sregex_iterator it = sregex_iterator(vars[i].begin(), vars[i].end(), eqSplit); it != sregex_iterator();
           it++) {
        splitMatch = *it;
        eq[pos] = splitMatch.str();
        pos++;
      }
      map<string, double>::iterator it;
      // checks if the var is already exist in the map and deletes its old value
      it = varsAndValues.find(eq[0]);
      if (it != varsAndValues.end()) {
        varsAndValues.erase(it);
      }
      // insert the new variable and its value to the map
      varsAndValues.insert(pair<string, double>(eq[0], stod(eq[1])));
    } else {
      throw "Illegal variable assignment";
    }
  }
  delete[] vars;
}

// the function creates an expression from postfix queue
Expression *Interpreter::postfixToExp(queue<string> qs) {
  Expression *e1;
  stack<Expression *> sEvaluate;
  while (!qs.empty()) {
    // checks if the front of the queue is a number
    if (checkIfNum(qs.front())) {
      // converts the string to double
      double number = stod(qs.front());
      Expression *numE = new Value(number);
      sEvaluate.push(numE);
      qs.pop();
      // checks if the string is an unary minus
    } else if (qs.front().compare("!-!") == 0) {
      Expression *unaryM = new UMinus(sEvaluate.top());
      sEvaluate.pop();
      sEvaluate.push(unaryM);
      qs.pop();
      // checks if the string is an unary plus
    } else if (qs.front().compare("!+!") == 0) {
      Expression *unaryP = new UPlus(sEvaluate.top());
      sEvaluate.pop();
      sEvaluate.push(unaryP);
      qs.pop();
      // checks if the string is an operator
    } else if (checkIfOp(qs.front())) {
      string op = qs.front();
      qs.pop();
      if (op.compare("+") == 0) {
        Expression *right = sEvaluate.top();
        sEvaluate.pop();
        Expression *left = sEvaluate.top();
        sEvaluate.pop();
        Expression *plusE = new Plus(left, right);
        sEvaluate.push(plusE);
      } else if (op.compare("-") == 0) {
        Expression *right = sEvaluate.top();
        sEvaluate.pop();
        Expression *left = sEvaluate.top();
        sEvaluate.pop();
        Expression *minusE = new Minus(left, right);
        sEvaluate.push(minusE);
      } else if (op.compare("/") == 0) {
        Expression *right = sEvaluate.top();
        sEvaluate.pop();
        Expression *left = sEvaluate.top();
        sEvaluate.pop();
        Expression *divE = new Div(left, right);
        sEvaluate.push(divE);
      } else {
        Expression *right = sEvaluate.top();
        sEvaluate.pop();
        Expression *left = sEvaluate.top();
        sEvaluate.pop();
        Expression *mulE = new Mul(left, right);
        sEvaluate.push(mulE);
      }
    } else {
      // checks if the variable is in the map
      if (checkIfInMapClientToSim(qs.front())) {
        Expression *var = new Variable(qs.front(), Maps::symbolTableClientToSim[qs.front()].first);
        sEvaluate.push(var);
        qs.pop();
      }else if(checkIfInMapSimToClient(qs.front())){
        Expression *var = new Variable(qs.front(), Maps::symbolTableSimToClient[qs.front()].first);
        sEvaluate.push(var);
        qs.pop();
      }else {
        throw "Undefined variable";
      }
    }
  }
  return sEvaluate.top();
}

// The function returns true if the string is an operator
bool Interpreter::checkIfOp(string s) {
  regex findOp(R"(^(\-|\+|\*|\/)$)");
  int count = distance(
      sregex_iterator(s.begin(), s.end(), findOp),
      sregex_iterator());
  return count == 1;
}

// The function returns true if the string is a number
bool Interpreter::checkIfNum(string s) {
  regex findNum("^(([0-9]+)|([0-9]+.[0-9]+))$");
  int count = distance(
      sregex_iterator(s.begin(), s.end(), findNum),
      sregex_iterator());
  return count == 1;
}

// The function returns true if the string is a valid equation (var=val)
bool Interpreter::checkValidEquation(string s) {
  regex findVar("^([A-Z]|[a-z]|\\_)([0-9]|\\_|[A-Z]|[a-z])*=(([0-9]+)|([0-9]+.[0-9]+))$");
  int count = distance(
      sregex_iterator(s.begin(), s.end(), findVar),
      sregex_iterator());
  return count == 1;
}

// The function returns true if the string is a variable
bool Interpreter::checkIfVariable(string s) {
  regex findVar("^([A-Z]|[a-z]|\\_)([0-9]|\\_|[A-Z]|[a-z])*$");
  int count = distance(
      sregex_iterator(s.begin(), s.end(), findVar),
      sregex_iterator());
  return count == 1;
}

// The function returns true if the string does not contains more than one operator in a row
bool Interpreter::checkValidNumOp(string s) {
  regex findMoreThanOneOp("(\\/|\\*|\\+|\\-|!-!|!+!){2,}");
  int count = distance(
      sregex_iterator(s.begin(), s.end(), findMoreThanOneOp),
      sregex_iterator());
  return count == 0;
}

// The function returns true if the string contains variables in parenthesis when there is Uminus/Uplus
bool Interpreter::checkVarAndP(string s) {
  regex findVarAndP(R"(((!+!|!-!)(\)|((\_)([0-9]|\_|[A-Z]|[a-z])*))))");
  int count = distance(
      sregex_iterator(s.begin(), s.end(), findVarAndP),
      sregex_iterator());
  return count == 0;
}

// The function returns true if the string contains valid attachment of parenthesis
bool Interpreter::checkParentheses(string s) {
  regex findInvalidP1("(\\(\\))");
  int count1 = distance(
      sregex_iterator(s.begin(), s.end(), findInvalidP1),
      sregex_iterator());
  regex findInvalidP2("(\\)\\()");
  int count2 = distance(
      sregex_iterator(s.begin(), s.end(), findInvalidP2),
      sregex_iterator());
  return (count1 + count2) == 0;
}

// The function returns true if the string has a valid order of parenthesis and vars/nums/operators
bool Interpreter::checkValidOrder(string s) {
  regex findInvalidOrder1(R"((([A-Z]|[a-z]|\_)([0-9]|\_|[A-Z]|[a-z])*|(([0-9]+)|([0-9]+.[0-9]+)))\()");
  int count1 = distance(
      sregex_iterator(s.begin(), s.end(), findInvalidOrder1),
      sregex_iterator());
  regex findInvalidOrder2(R"(\)(([A-Z]|[a-z]|\_)([0-9]|\_|[A-Z]|[a-z])*|(([0-9]+)|([0-9]+.[0-9]+))))");
  int count2 = distance(
      sregex_iterator(s.begin(), s.end(), findInvalidOrder2),
      sregex_iterator());
  regex findInvalidOrder3(R"(((\+|\-|\*|\/)(\))|(\+|\-|\*|\/)$))");
  int count3 = distance(
      sregex_iterator(s.begin(), s.end(), findInvalidOrder3),
      sregex_iterator());
  return (count1 + count2 + count3) == 0;
}

// // The function returns true if the map ClientToSim contains the string
bool Interpreter::checkIfInMapClientToSim(string s) {
  return !(Maps::symbolTableClientToSim.find(s) == Maps::symbolTableClientToSim.end());
}

// // The function returns true if the map contains the string
bool Interpreter::checkIfInMapSimToClient(string s) {
  return !(Maps::symbolTableSimToClient.find(s) == Maps::symbolTableSimToClient.end());
}
//
// Created by chen96 on 28/12/2019.
//

#ifndef FLIGHTGEAR__EXPRESSIONCALCULATE_H_
#define FLIGHTGEAR__EXPRESSIONCALCULATE_H_


#include "Expression.h"
#include <string>
#include <queue>
#include <map>

using namespace std;

class Value : public Expression {
 private:
  const double val;
 public:
  Value(double);
  double calculate() override;
  virtual ~Value();
};

class BinaryOperator : public Expression {
 protected:
  Expression *left;
  Expression *right;
 public:
  BinaryOperator(Expression *, Expression *);
  virtual ~BinaryOperator();
};

class UnaryOperator : public Expression {
 protected:
  Expression *exp;
 public:
  UnaryOperator(Expression *);
  virtual ~UnaryOperator();
};

class Variable : public Expression {
 private:
  string name;
  double value;
 public:
  Variable(string, double);
  double calculate() override;
  Variable &operator++(); // ++X
  Variable &operator--(); // --x
  Variable &operator+=(double);
  Variable &operator-=(double);
  Variable &operator++(int); // x++
  Variable &operator--(int); // x--
  virtual ~Variable();
};

class Plus : public BinaryOperator {
 public:
  Plus(Expression *, Expression *);
  double calculate() override;
  ~Plus();
};

class Minus : public BinaryOperator {
 public:
  Minus(Expression *, Expression *);
  double calculate() override;
  ~Minus();
};

class Mul : public BinaryOperator {
 public:
  Mul(Expression *, Expression *);
  double calculate() override;
  ~Mul();
};

class Div : public BinaryOperator {
 public:
  Div(Expression *, Expression *);
  double calculate() override;
  ~Div();
};

class UPlus : public UnaryOperator {
 public:
  UPlus(Expression *);
  double calculate() override;
  ~UPlus();
};

class UMinus : public UnaryOperator {
 public:
  UMinus(Expression *);
  double calculate() override;
  ~UMinus();
};

class Interpreter {
 private:
  map<string, int> precedence;
  map<string, double> varsAndValues;
 public:
  Interpreter();
  Expression *interpret(string);
  void setVariables(string);
  bool checkIfVariable(string);
  bool checkIfNum(string);
  bool checkIfOp(string);
  Expression *postfixToExp(queue<string>);
  int getOpPrecedence(string);
  bool checkValidNumOp(string);
  bool checkValidEquation(string);
  bool checkVarAndP(string);
  bool checkParentheses(string);
  bool checkValidOrder(string);
  bool checkIfInMap(string);
};

#endif //FLIGHTGEAR__EXPRESSIONCALCULATE_H_

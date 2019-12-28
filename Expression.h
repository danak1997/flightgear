//
// Created by chen96 on 28/12/2019.
//

#ifndef FLIGHTGEAR__EXPRESSION_H_
#define FLIGHTGEAR__EXPRESSION_H_

using namespace std;
/**
 * Expression Interface
 */
class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() {}
};
#endif //FLIGHTGEAR__EXPRESSION_H_

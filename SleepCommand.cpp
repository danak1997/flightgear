//
// Created by chen96 on 22/12/2019.
//

#include "SleepCommand.h"
#include "ExpressionCalculate.h"
#include <thread>
#include <algorithm>

int SleepCommand::execute(vector<string> params) {
  Interpreter *i = new Interpreter();
  Expression *answer = nullptr;
  string::iterator end_pos = remove(params[1].begin(), params[1].end(), ' ');
  params[1].erase(end_pos, params[1].end());
  end_pos = remove(params[1].begin(), params[1].end(), '\t');
  params[1].erase(end_pos, params[1].end());
  answer = i->interpret(params[1]);
  int answerResult = answer->calculate();
  this_thread::sleep_for(chrono::milliseconds(answerResult));
  return 2;
}

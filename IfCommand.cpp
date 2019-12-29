//
// Created by duni on 22/12/2019.
//

#include "IfCommand.h"
#include "Maps.h"
#include "SetCommand.h"
#include "ExpressionCalculate.h"
#include <algorithm>

int IfCommand::execute(vector<string> params) {
  int index = 0;
  int returnCount = 0;
  bool booleanCondition = false;
  Command *c;
  auto first = params.begin();
  auto last = params.begin();
  advance(last, 4);
  vector<string> conditionVec(first,last);
  vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
  iteratorBegin = params.begin();
  advance(iteratorEnd, 5);
  params.erase(iteratorBegin, iteratorEnd);
  returnCount+=5;
  Interpreter *i = new Interpreter();
  Expression *left = nullptr;
  Expression *right = nullptr;
  try {
    string::iterator end_pos = remove(conditionVec[1].begin(), conditionVec[1].end(), ' ');
    conditionVec[1].erase(end_pos, conditionVec[1].end());
    end_pos = remove(conditionVec[1].begin(), conditionVec[1].end(), '\t');
    conditionVec[1].erase(end_pos, conditionVec[1].end());
    left = i->interpret(conditionVec[1]);
    double answerLeft = left->calculate();
    end_pos = remove(conditionVec[3].begin(), conditionVec[3].end(), ' ');
    conditionVec[3].erase(end_pos, conditionVec[3].end());
    end_pos = remove(conditionVec[3].begin(), conditionVec[3].end(), '\t');
    conditionVec[3].erase(end_pos, conditionVec[3].end());
    right = i->interpret(conditionVec[3]);
    double answerRight = right->calculate();
    if (conditionVec[2].compare("<") == 0) {
      if (answerLeft < answerRight) {
        booleanCondition = true;
      }
    } else if (conditionVec[2].compare(">") == 0) {
      if (answerLeft > answerRight) {
        booleanCondition = true;
      }
    } else if (conditionVec[2].compare("<=") == 0) {
      if (answerLeft <= answerRight) {
        booleanCondition = true;
      }
    } else if (conditionVec[2].compare(">=") == 0) {
      if (answerLeft >= answerRight) {
        booleanCondition = true;
      }
    } else if (conditionVec[2].compare("==") == 0) {
      if (answerLeft == answerRight) {
        booleanCondition = true;
      }
    } else {
      if (answerLeft != answerRight) {
        booleanCondition = true;
      }
    }
    if (booleanCondition) {
      while (index < params.size()) {
        index = 0;
        string::iterator end_pos = remove(params[index].begin(), params[index].end(), ' ');
        params[index].erase(end_pos, params[index].end());
        end_pos = remove(params[index].begin(), params[index].end(), '\t');
        params[index].erase(end_pos, params[index].end());
        if (params[index] == "}") {
          returnCount++;
          break;
        } else if (Maps::CommandMap[params[index]] == nullptr) {
          c = new SetCommand();
        } else {
          c = Maps::CommandMap.at(params[index]);
        }
        if (c != nullptr) {
          index += c->execute(params);
          returnCount += index;
        }
        iteratorEnd = params.begin();
        iteratorBegin = params.begin();
        advance(iteratorEnd, index);
        params.erase(iteratorBegin, iteratorEnd);
      }
    } else{
      index = 0;
      while(params[index].compare("}")!=0){
        index++;
      }
      returnCount += index + 1;
    }
  }
  catch (const char *e) {
    if (e != nullptr) {
      delete e;
      delete i;
    }
  }

  return returnCount;
}


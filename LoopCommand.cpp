//
// Created by duni on 22/12/2019.
//

#include "LoopCommand.h"
#include "ExpressionCalculate.h"
#include "Maps.h"
#include "SetCommand.h"
#include <algorithm>
#include <iostream>

int LoopCommand::execute(vector<string> params) {
  int index = 0;
  int returnCount = 0;
  int currCell = 0;
  Command *c;
  vector<string> block;
  auto first = params.begin();
  auto last = params.begin();
  advance(last, 4);
  vector<string> conditionVec(first, last);
  vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
  iteratorBegin = params.begin();
  advance(iteratorEnd, 5);
  params.erase(iteratorBegin, iteratorEnd);
  returnCount += 5;
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
    while (resultCondition(answerLeft, answerRight, conditionVec[2])) {
      currCell = 0;
      while(params[currCell].compare("}")!=0){
        block.emplace_back(params[currCell]);
        currCell++;
      }
      index = 0;
      while (block.size() > 0) {
        index = 0;
        bool isCSetCommand = false;
        string::iterator end_pos = remove(block[index].begin(), block[index].end(), ' ');
        block[index].erase(end_pos, block[index].end());
        end_pos = remove(block[index].begin(), block[index].end(), '\t');
        block[index].erase(end_pos, block[index].end());
        if (Maps::CommandMap.find(block[index])==Maps::CommandMap.end()) {
          c = new SetCommand();
          isCSetCommand = true;
        } else {
          c = Maps::CommandMap.at(block[index]);
        }
        if (c != nullptr) {
          index += c->execute(block);
          if (isCSetCommand) {
            delete c;
          }
        }
        iteratorEnd = block.begin();
        iteratorBegin = block.begin();
        advance(iteratorEnd, index);
        block.erase(iteratorBegin, iteratorEnd);
      }
      left = i->interpret(conditionVec[1]);
      answerLeft = left->calculate();
      right = i->interpret(conditionVec[3]);
      answerRight = right->calculate();
    }
    index = 0;
    while (params[index].compare("}") != 0) {
      index++;
    }
    returnCount += index + 1;
  }
  catch (const char *e) {
    if (e != nullptr) {
      cout <<"no" << endl;
      delete e;
      delete i;
    }
  }

  return returnCount;
}

bool LoopCommand::resultCondition(double answerLeft, double answerRight, string op) {
  if (op.compare("<") == 0) {
    return (answerLeft < answerRight);
  } else if (op.compare(">") == 0) {
    return (answerLeft > answerRight);
  } else if (op.compare("<=") == 0) {
    return (answerLeft <= answerRight);
  } else if (op.compare(">=") == 0) {
    return (answerLeft >= answerRight);
  } else if (op.compare("==") == 0) {
    return (abs(answerLeft - answerRight) <0.0001 );
  } else {
    return (abs(answerLeft - answerRight) >= 0.0001 );
  }
}


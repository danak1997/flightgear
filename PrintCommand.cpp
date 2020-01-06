//
// Created by duni on 22/12/2019.
//

#include <iostream>
#include "PrintCommand.h"
#include "globalVariables.h"
#include "ExpressionCalculate.h"
#include <algorithm>

int PrintCommand::execute(vector<string> params) {
  // Check if the parameter in the print command is an expression or a string
  if (doesDelimExist(params[1], '"')) {
    cout << params[1].substr(1, params[1].length() - 2) << endl;
  } else {
    // If it is an expression - then calculate
    Interpreter *i = new Interpreter();
    Expression *answer = nullptr;
    // Remove spaces
    string::iterator end_pos = remove(params[1].begin(), params[1].end(), ' ');
    params[1].erase(end_pos, params[1].end());
    // Remove tabs
    end_pos = remove(params[1].begin(), params[1].end(), '\t');
    params[1].erase(end_pos, params[1].end());
    // Calculate
    answer = i->interpret(params[1]);
    double answerResult = answer->calculate();
    cout << answerResult << endl;
  }
  return 2;
}

// This function checks if the print command parameter is a string - surrounded by brackets
bool PrintCommand::doesDelimExist(string line, char delim) {
  char currChar;
  int i;
  for (i = 0; i < line.length(); i++) {
    currChar = line[i];
    if (currChar == delim) {
      return true;
    }
  }
  return false;
}
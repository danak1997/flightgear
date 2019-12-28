//
// Created by duni on 22/12/2019.
//

#include "ConditionParser.h"

ConditionParser::ConditionParser(vector<string> booleanCondition, vector<Command> blockCommands) {
  this->blockCommands = blockCommands;
  this->booleanCondition = booleanCondition;
}
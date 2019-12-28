//
// Created by duni on 22/12/2019.
//

#include "IfCommand.h"

int IfCommand::execute(vector<string> params, bool isConditionInvoked) {

}

IfCommand::IfCommand(vector<string> booleanCondition,vector<Command> blockCommands) : ConditionParser(booleanCondition, blockCommands) {}
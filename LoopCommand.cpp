//
// Created by duni on 22/12/2019.
//

#include "LoopCommand.h"

int LoopCommand::execute(vector<string> params, bool isConditionInvoked) {

}

LoopCommand::LoopCommand(vector<string> booleanCondition,vector<Command> blockCommands) : ConditionParser(booleanCondition, blockCommands) {}
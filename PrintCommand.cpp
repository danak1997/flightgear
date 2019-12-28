//
// Created by duni on 22/12/2019.
//

#include <iostream>
#include "PrintCommand.h"
#include "Maps.h"

int PrintCommand::execute(vector<string> params, bool isConditionInvoked) {
  if(isConditionInvoked) {
    cout << params[1].substr(1, params[1].length() - 2) << endl;
  }
    return 2;
}
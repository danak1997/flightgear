//
// Created by chen96 on 22/12/2019.
//

#include "SleepCommand.h"
#include <thread>

int SleepCommand::execute(vector<string> params, bool isConditionInvoked) {
  if(isConditionInvoked) {
    int num = stoi(params[1]);
    this_thread::sleep_for(chrono::milliseconds(num));
  }
  return 2;
}

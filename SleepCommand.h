//
// Created by chen96 on 22/12/2019.
//

#ifndef FLIGHTGEAR__SLEEPCOMMAND_H_
#define FLIGHTGEAR__SLEEPCOMMAND_H_

#include "Command.h"
#include <vector>
#include <string>
using namespace std;

class SleepCommand : public Command{
  int execute(vector<string>,bool);
  //virtual ~SleepCommand();
};

#endif //FLIGHTGEAR__SLEEPCOMMAND_H_

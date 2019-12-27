//
// Created by chen96 on 27/12/2019.
//

#ifndef FLIGHTGEAR__SETCOMMAND_H_
#define FLIGHTGEAR__SETCOMMAND_H_

#include "Command.h"

using namespace std;
class SetCommand : public Command{
 public:
  int execute(vector<string>);
};

#endif //FLIGHTGEAR__SETCOMMAND_H_

//
// Created by chen96 on 22/12/2019.
//

#ifndef FLIGHTGEAR__DEFINEVARCOMMAND_H_
#define FLIGHTGEAR__DEFINEVARCOMMAND_H_

#include "Command.h"
#include <vector>
#include <string>
using namespace std;

class DefineVarCommand : public Command{
 public:
  int execute(vector<string>,bool);
  //virtual ~DefineVarCommand();
};

#endif //FLIGHTGEAR__DEFINEVARCOMMAND_H_

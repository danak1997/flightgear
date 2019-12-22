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
 private:
  vector<string> params;
 public:
  DefineVarCommand (vector<string>);
  int execute();
  virtual ~DefineVarCommand();
};

#endif //FLIGHTGEAR__DEFINEVARCOMMAND_H_

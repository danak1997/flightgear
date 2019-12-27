//
// Created by chen96 on 22/12/2019.
//

#include "DefineVarCommand.h"
#include "Maps.h"

int DefineVarCommand::execute(vector<string> params) {
  if (params[2].compare("->") == 0) {

  } else if (params[2].compare("<-") == 0) {
    string sim = params[4];
    sim = sim.substr(1, sim.length() - 2);
    Maps::symbolTableSimToClient[params[1]] = make_pair(0, sim);
  } else {

  }

  return 5;
}
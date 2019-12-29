//
// Created by chen96 on 22/12/2019.
//

#include "DefineVarCommand.h"
#include "Maps.h"
#include <algorithm>

int DefineVarCommand::execute(vector<string> params) {
  string::iterator end_pos = remove(params[1].begin(), params[1].end(), ' ');
  params[1].erase(end_pos, params[1].end());
  end_pos = remove(params[1].begin(), params[1].end(), '\t');
  params[1].erase(end_pos, params[1].end());
  if (params[2].compare("->") == 0) {
    string sim = params[4];
    sim = sim.substr(1, sim.length() - 2);
    Maps::symbolTableClientToSim[params[1]] = make_pair(0, sim);
  } else if (params[2].compare("<-") == 0) {
    string sim = params[4];
    sim = sim.substr(1, sim.length() - 2);
    Maps::symbolTableSimToClient[params[1]] = make_pair(0, sim);
  } else {

  }
  return 5;
}
//
// Created by chen96 on 22/12/2019.
//

#include "DefineVarCommand.h"
#include "Maps.h"
#include "ExpressionCalculate.h"
#include <algorithm>
#include <iostream>

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
    end_pos = remove(params[3].begin(), params[3].end(), ' ');
    params[3].erase(end_pos, params[3].end());
    end_pos = remove(params[3].begin(), params[3].end(), '\t');
    params[3].erase(end_pos, params[3].end());
    if(checkIfInMapSimToClient(params[3])){
      float value = Maps::symbolTableSimToClient[params[3]].first;
      Maps::symbolTableSimToClient[params[1]] = make_pair(value, 0);
      return 4;
    }else if(checkIfInMapClientToSim(params[3])){
      float value = Maps::symbolTableClientToSim[params[3]].first;
      Maps::symbolTableClientToSim[params[1]] = make_pair(value, 0);
      return 4;
    }else{
      cout << "Variable not found in symbolTable" << endl;
      exit(1);
    }
  }

  return 5;
}

// // The function returns true if the map ClientToSim contains the string
bool DefineVarCommand::checkIfInMapClientToSim(string s) {
  return !(Maps::symbolTableClientToSim.find(s) == Maps::symbolTableClientToSim.end());
}

// // The function returns true if the map SimToClient contains the string
bool DefineVarCommand::checkIfInMapSimToClient(string s) {
  return !(Maps::symbolTableSimToClient.find(s) == Maps::symbolTableSimToClient.end());
}
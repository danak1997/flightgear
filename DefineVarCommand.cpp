//
// Created by chen96 on 22/12/2019.
//

#include "DefineVarCommand.h"
#include "globalVariables.h"
#include "ExpressionCalculate.h"
#include <algorithm>
#include <iostream>

int DefineVarCommand::execute(vector<string> params) {
    // Remove spaces
  string::iterator end_pos = remove(params[1].begin(), params[1].end(), ' ');
  params[1].erase(end_pos, params[1].end());
  // Remove tabs
  end_pos = remove(params[1].begin(), params[1].end(), '\t');
  params[1].erase(end_pos, params[1].end());
  // Check which symbol table is the current one according to the direction of the arrow
  if (params[2].compare("->") == 0) {
      // Set the sim - the path of the variable
    string sim = params[4];
    sim = sim.substr(1, sim.length() - 2);
      globalVariables::symbolTableClientToSim[params[1]] = make_pair(0, sim);
  } else if (params[2].compare("<-") == 0) {
      // Set the sim - the path of the variable
    string sim = params[4];
    sim = sim.substr(1, sim.length() - 2);
      globalVariables::symbolTableSimToClient[params[1]] = make_pair(0, sim);
      // The treatment in cases of an operand "=" inside the var command instead of arrows
  } else {
      // Remove spaces
    end_pos = remove(params[3].begin(), params[3].end(), ' ');
    params[3].erase(end_pos, params[3].end());
    // Remove tabs
    end_pos = remove(params[3].begin(), params[3].end(), '\t');
    params[3].erase(end_pos, params[3].end());
    // Check if the current variable is located in the sim to client symbol table, and set it's value accordingly
    if(checkIfInMapSimToClient(params[3])){
      float value = globalVariables::symbolTableSimToClient[params[3]].first;
        globalVariables::symbolTableSimToClient[params[1]] = make_pair(value, 0);
      return 4;
        // Check if the current variable is located in the client to sim symbol table, and set it's value accordingly
    }else if(checkIfInMapClientToSim(params[3])){
      float value = globalVariables::symbolTableClientToSim[params[3]].first;
        globalVariables::symbolTableClientToSim[params[1]] = make_pair(value, 0);
      return 4;
      // If the variable doesn't exist in any of the symbol tables - throw an exception
    }else{
      cout << "Variable not found in symbolTable" << endl;
      exit(1);
    }
  }

  return 5;
}

// // The function returns true if the map ClientToSim contains the string
bool DefineVarCommand::checkIfInMapClientToSim(string s) {
  return !(globalVariables::symbolTableClientToSim.find(s) == globalVariables::symbolTableClientToSim.end());
}

// // The function returns true if the map SimToClient contains the string
bool DefineVarCommand::checkIfInMapSimToClient(string s) {
  return !(globalVariables::symbolTableSimToClient.find(s) == globalVariables::symbolTableSimToClient.end());
}
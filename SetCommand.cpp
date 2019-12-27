//
// Created by chen96 on 27/12/2019.
//

#include "SetCommand.h"
#include "Maps.h"
#include <cstring>
#include <netinet/in.h>

int SetCommand::execute(vector<string> params) {
  Maps::symbolTableClientToSim[params[0]].first = stof(params[2]);
  string setCommandToSim = "set ";
  setCommandToSim+=Maps::symbolTableClientToSim[params[0]].second;
  setCommandToSim+=" ";
  setCommandToSim+=params[2];
  setCommandToSim+="\r\n";
  const char *setCommandToSend = setCommandToSim.c_str();
  send(Maps::socketId,setCommandToSend,strlen(setCommandToSend),0);
  return 3;
}

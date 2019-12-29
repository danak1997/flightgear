//
// Created by chen96 on 27/12/2019.
//

#include "SetCommand.h"
#include "Maps.h"
#include "ExpressionCalculate.h"
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <algorithm>

int SetCommand::execute(vector<string> params) {
  Interpreter *i = new Interpreter();
  Expression *e = nullptr;
  try {
    string::iterator end_pos = remove(params[2].begin(), params[2].end(), ' ');
    params[2].erase(end_pos, params[2].end());
    end_pos = remove(params[2].begin(), params[2].end(), '\t');
    params[2].erase(end_pos, params[2].end());
    end_pos = remove(params[0].begin(), params[0].end(), ' ');
    params[0].erase(end_pos, params[0].end());
    end_pos = remove(params[0].begin(), params[0].end(), '\t');
    params[0].erase(end_pos, params[0].end());
    e = i->interpret(params[2]);
    double answer = e->calculate();
    float floatAnswer = (float) answer;
    string stringAnswer = to_string(floatAnswer);
    Maps::symbolTableClientToSim[params[0]].first = floatAnswer;
    string setCommandToSim = "set ";
    setCommandToSim += Maps::symbolTableClientToSim[params[0]].second;
    setCommandToSim += " ";
    setCommandToSim += stringAnswer;
    setCommandToSim += "\r\n";
    const char *setCommandToSend = setCommandToSim.c_str();
    send(Maps::socketId, setCommandToSend, strlen(setCommandToSend), 0);
    delete e;
    delete i;
  } catch (const char *e) {
    if (e != nullptr) {
      delete e;
      delete i;
    }
  }
  return 3;
}

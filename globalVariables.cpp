//
// Created by chen96 on 27/12/2019.
//
#include "globalVariables.h"

namespace globalVariables {
 map<string, float> xmlMap = map<string, float>();
 map<string, pair<float, string>> symbolTableSimToClient = map<string, pair<float, string>>();
 map<string, pair<float, string>> symbolTableClientToSim = map<string, pair<float, string>>();
 map<string, Command*> CommandMap = map<string, Command*>();
 int socketId = -1;
 mutex symbolTableMutex;
}

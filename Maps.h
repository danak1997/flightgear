//
// Created by chen96 on 26/12/2019.
//

#ifndef FLIGHTGEAR__MAPS_H_
#define FLIGHTGEAR__MAPS_H_
#include <string>
#include <map>
#include "Command.h"
using namespace std;

namespace Maps {
extern map<string, float> xmlMap;
extern map<string, pair<float, string>> symbolTableSimToClient;
extern map<string, pair<float, string>> symbolTableClientToSim;
extern map<string, Command *> CommandMap;
extern int socketId;
}

#endif //FLIGHTGEAR__MAPS_H_

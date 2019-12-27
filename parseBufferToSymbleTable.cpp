//
// Created by duni on 23/12/2019.
//

#include <cstring>
#include <vector>
#include "parseBufferToSymbleTable.h"
#include "Maps.h"

void parseBufferToSymbolTable::parseBufferAnsSymbolTables(string buffer) {
  vector<float> bufferArray;
  char *currValue;
  float valueToInsert;
  char bufferToStrTok[buffer.length() + 1];
  strcpy(bufferToStrTok, buffer.c_str());
  currValue = strtok(bufferToStrTok, ",");
  while (currValue) {
    valueToInsert = atof(currValue);
    bufferArray.emplace_back(valueToInsert);
    currValue = strtok(nullptr, ",");
  }
  Maps::xmlMap["/instrumentation/airspeed-indicator/indicated-speed-kt"] = bufferArray[0];
  Maps::xmlMap["/sim/time/warp"] = bufferArray[1];
  Maps::xmlMap["/controls/switches/magnetos"] = bufferArray[2];
  Maps::xmlMap["/instrumentation/heading-indicator/offset-deg"] = bufferArray[3];
  Maps::xmlMap["/instrumentation/altimeter/indicated-altitude-ft"] = bufferArray[4];
  Maps::xmlMap["/instrumentation/altimeter/pressure-alt-ft"] = bufferArray[5];
  Maps::xmlMap["/instrumentation/attitude-indicator/indicated-pitch-deg"] = bufferArray[6];
  Maps::xmlMap["/instrumentation/attitude-indicator/indicated-roll-deg"] = bufferArray[7];
  Maps::xmlMap["/instrumentation/attitude-indicator/internal-pitch-deg"] = bufferArray[8];
  Maps::xmlMap["/instrumentation/attitude-indicator/internal-roll-deg"] = bufferArray[9];
  Maps::xmlMap["/instrumentation/encoder/indicated-altitude-ft"] = bufferArray[10];
  Maps::xmlMap["/instrumentation/encoder/pressure-alt-ft"] = bufferArray[11];
  Maps::xmlMap["/instrumentation/gps/indicated-altitude-ft"] = bufferArray[12];
  Maps::xmlMap["/instrumentation/gps/indicated-ground-speed-kt"] = bufferArray[13];
  Maps::xmlMap["/instrumentation/gps/indicated-vertical-speed"] = bufferArray[14];
  Maps::xmlMap["/instrumentation/heading-indicator/indicated-heading-deg"] = bufferArray[15];
  Maps::xmlMap["/instrumentation/magnetic-compass/indicated-heading-deg"] = bufferArray[16];
  Maps::xmlMap["/instrumentation/slip-skid-ball/indicated-slip-skid"] = bufferArray[17];
  Maps::xmlMap["/instrumentation/turn-indicator/indicated-turn-rate"] = bufferArray[18];
  Maps::xmlMap["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = bufferArray[19];
  Maps::xmlMap["/controls/flight/aileron"] = bufferArray[20];
  Maps::xmlMap["/controls/flight/elevator"] = bufferArray[21];
  Maps::xmlMap["/controls/flight/rudder"] = bufferArray[22];
  Maps::xmlMap["/controls/flight/flaps"] = bufferArray[23];
  Maps::xmlMap["/controls/engines/engine/throttle"] = bufferArray[24];
  Maps::xmlMap["/controls/engines/current-engine/throttle"] = bufferArray[25];
  Maps::xmlMap["/controls/switches/master-avionics"] = bufferArray[26];
  Maps::xmlMap["/controls/switches/starter"] = bufferArray[27];
  Maps::xmlMap["/engines/active-engine/auto-start"] = bufferArray[28];
  Maps::xmlMap["/controls/flight/speedbrake"] = bufferArray[29];
  Maps::xmlMap["/sim/model/c172p/brake-parking"] = bufferArray[30];
  Maps::xmlMap["/controls/engines/engine/primer"] = bufferArray[31];
  Maps::xmlMap["/controls/engines/current-engine/mixture"] = bufferArray[32];
  Maps::xmlMap["/controls/switches/master-bat"] = bufferArray[33];
  Maps::xmlMap["/controls/switches/master-alt"] = bufferArray[34];
  Maps::xmlMap["/engines/engine/rpm"] = bufferArray[35];
}

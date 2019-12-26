//
// Created by duni on 23/12/2019.
//

#include <cstring>
#include <vector>
#include "parseBufferToSymbleTable.h"

map<std::__cxx11::string, float> parseBufferToSymbolTable::parseBufferAnsSymbolTables(string buffer) {
    vector<float > bufferArray;
    map<string, float> xmlMap;
    char delim = ',';
    char* currValue;
    float valueToInsert;
    char bufferToStrTok[buffer.length() + 1];
    strcpy(bufferToStrTok, buffer.c_str());
    currValue = strtok(bufferToStrTok, ",");
    while (bufferToStrTok) {
        valueToInsert = stof(currValue);
        bufferArray.emplace_back(valueToInsert);
        currValue = strtok(nullptr, ",");
    }
    xmlMap.insert({"/instrumentation/airspeed-indicator/indicated-speed-kt", bufferArray[0]});
    xmlMap.insert({"/sim/time/warp", bufferArray[1]});
    xmlMap.insert({"/controls/switches/magnetos", bufferArray[3]});
    xmlMap.insert({"/instrumentation/heading-indicator/offset-deg", bufferArray[4]});
    xmlMap.insert({"/instrumentation/altimeter/indicated-altitude-ft", bufferArray[5]});
    xmlMap.insert({"/instrumentation/altimeter/pressure-alt-ft", bufferArray[6]});
    xmlMap.insert({"/instrumentation/attitude-indicator/indicated-pitch-deg", bufferArray[7]});
    xmlMap.insert({"/instrumentation/attitude-indicator/indicated-roll-deg", bufferArray[8]});
    xmlMap.insert({"/instrumentation/attitude-indicator/internal-pitch-deg", bufferArray[9]});
    xmlMap.insert({"/instrumentation/attitude-indicator/internal-roll-deg", bufferArray[10]});
    xmlMap.insert({"/instrumentation/encoder/indicated-altitude-ft", bufferArray[11]});
    xmlMap.insert({"/instrumentation/encoder/pressure-alt-ft", bufferArray[12]});
    xmlMap.insert({"/instrumentation/gps/indicated-altitude-ft", bufferArray[13]});
    xmlMap.insert({"/instrumentation/gps/indicated-ground-speed-kt", bufferArray[14]});
    xmlMap.insert({"/instrumentation/gps/indicated-vertical-speed", bufferArray[15]});
    xmlMap.insert({"/instrumentation/heading-indicator/indicated-heading-deg", bufferArray[16]});
    xmlMap.insert({"/instrumentation/magnetic-compass/indicated-heading-deg", bufferArray[17]});
    xmlMap.insert({"/instrumentation/slip-skid-ball/indicated-slip-skid", bufferArray[18]});
    xmlMap.insert({"/instrumentation/turn-indicator/indicated-turn-rate", bufferArray[19]});
    xmlMap.insert({"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", bufferArray[20]});
    xmlMap.insert({"/controls/flight/aileron", bufferArray[21]});
    xmlMap.insert({"/controls/flight/elevator", bufferArray[22]});
    xmlMap.insert({"/controls/flight/rudder", bufferArray[23]});
    xmlMap.insert({"/controls/flight/flaps", bufferArray[24]});
    xmlMap.insert({"/controls/engines/engine/throttle", bufferArray[25]});
    xmlMap.insert({"/controls/engines/current-engine/throttle", bufferArray[26]});
    xmlMap.insert({"/controls/switches/master-avionics", bufferArray[27]});
    xmlMap.insert({"/controls/switches/starter", bufferArray[28]});
    xmlMap.insert({"/engines/active-engine/auto-start", bufferArray[29]});
    xmlMap.insert({"/controls/flight/speedbrake", bufferArray[30]});
    xmlMap.insert({"/sim/model/c172p/brake-parking", bufferArray[31]});
    xmlMap.insert({"/controls/engines/engine/primer", bufferArray[32]});
    xmlMap.insert({"/controls/engines/current-engine/mixture", bufferArray[33]});
    xmlMap.insert({"/controls/switches/master-bat", bufferArray[34]});
    xmlMap.insert({"/controls/switches/master-alt", bufferArray[35]});
    xmlMap.insert({"/engines/engine/rpm", bufferArray[36]});
    return xmlMap;
}

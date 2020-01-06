//
// Created by duni on 23/12/2019.
//

#include <cstring>
#include <vector>
#include "parseBufferToSymbleTable.h"
#include "globalVariables.h"

void parseBufferToSymbolTable::parseBufferAnsSymbolTables(const string &buffer) {
    vector<float> bufferArray;
    char *currValue;
    float valueToInsert;
    char bufferToStrTok[buffer.length() + 1];
    strcpy(bufferToStrTok, buffer.c_str());
    currValue = strtok(bufferToStrTok, ",");
    // Split the buffer according to commas
    while (currValue) {
        valueToInsert = atof(currValue);
        bufferArray.emplace_back(valueToInsert);
        currValue = strtok(nullptr, ",");
    }

    // Create the xml map - put all of the values that the simulator sent in the suitable keys
    globalVariables::xmlMap["/instrumentation/airspeed-indicator/indicated-speed-kt"] = bufferArray[0];
    globalVariables::xmlMap["/sim/time/warp"] = bufferArray[1];
    globalVariables::xmlMap["/controls/switches/magnetos"] = bufferArray[2];
    globalVariables::xmlMap["/instrumentation/heading-indicator/offset-deg"] = bufferArray[3];
    globalVariables::xmlMap["/instrumentation/altimeter/indicated-altitude-ft"] = bufferArray[4];
    globalVariables::xmlMap["/instrumentation/altimeter/pressure-alt-ft"] = bufferArray[5];
    globalVariables::xmlMap["/instrumentation/attitude-indicator/indicated-pitch-deg"] = bufferArray[6];
    globalVariables::xmlMap["/instrumentation/attitude-indicator/indicated-roll-deg"] = bufferArray[7];
    globalVariables::xmlMap["/instrumentation/attitude-indicator/internal-pitch-deg"] = bufferArray[8];
    globalVariables::xmlMap["/instrumentation/attitude-indicator/internal-roll-deg"] = bufferArray[9];
    globalVariables::xmlMap["/instrumentation/encoder/indicated-altitude-ft"] = bufferArray[10];
    globalVariables::xmlMap["/instrumentation/encoder/pressure-alt-ft"] = bufferArray[11];
    globalVariables::xmlMap["/instrumentation/gps/indicated-altitude-ft"] = bufferArray[12];
    globalVariables::xmlMap["/instrumentation/gps/indicated-ground-speed-kt"] = bufferArray[13];
    globalVariables::xmlMap["/instrumentation/gps/indicated-vertical-speed"] = bufferArray[14];
    globalVariables::xmlMap["/instrumentation/heading-indicator/indicated-heading-deg"] = bufferArray[15];
    globalVariables::xmlMap["/instrumentation/magnetic-compass/indicated-heading-deg"] = bufferArray[16];
    globalVariables::xmlMap["/instrumentation/slip-skid-ball/indicated-slip-skid"] = bufferArray[17];
    globalVariables::xmlMap["/instrumentation/turn-indicator/indicated-turn-rate"] = bufferArray[18];
    globalVariables::xmlMap["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = bufferArray[19];
    globalVariables::xmlMap["/controls/flight/aileron"] = bufferArray[20];
    globalVariables::xmlMap["/controls/flight/elevator"] = bufferArray[21];
    globalVariables::xmlMap["/controls/flight/rudder"] = bufferArray[22];
    globalVariables::xmlMap["/controls/flight/flaps"] = bufferArray[23];
    globalVariables::xmlMap["/controls/engines/engine/throttle"] = bufferArray[24];
    globalVariables::xmlMap["/controls/engines/current-engine/throttle"] = bufferArray[25];
    globalVariables::xmlMap["/controls/switches/master-avionics"] = bufferArray[26];
    globalVariables::xmlMap["/controls/switches/starter"] = bufferArray[27];
    globalVariables::xmlMap["/engines/active-engine/auto-start"] = bufferArray[28];
    globalVariables::xmlMap["/controls/flight/speedbrake"] = bufferArray[29];
    globalVariables::xmlMap["/sim/model/c172p/brake-parking"] = bufferArray[30];
    globalVariables::xmlMap["/controls/engines/engine/primer"] = bufferArray[31];
    globalVariables::xmlMap["/controls/engines/current-engine/mixture"] = bufferArray[32];
    globalVariables::xmlMap["/controls/switches/master-bat"] = bufferArray[33];
    globalVariables::xmlMap["/controls/switches/master-alt"] = bufferArray[34];
    globalVariables::xmlMap["/engines/engine/rpm"] = bufferArray[35];
}

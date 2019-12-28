//
// Created by duni on 22/12/2019.
//

#ifndef FLIGHTGEAR_LOOPCOMMAND_H
#define FLIGHTGEAR_LOOPCOMMAND_H

#include "ConditionParser.h"
#include <vector>
#include <string>

using namespace std;

class LoopCommand : public ConditionParser {
public:
    LoopCommand(vector<string>,vector<Command>);
    int execute(vector<string>, bool);
    //virtual ~LoopCommand();
};


#endif //FLIGHTGEAR_LOOPCOMMAND_H

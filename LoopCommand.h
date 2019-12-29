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
    int execute(vector<string>);
    //virtual ~LoopCommand();
};


#endif //FLIGHTGEAR_LOOPCOMMAND_H

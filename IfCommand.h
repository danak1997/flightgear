//
// Created by duni on 22/12/2019.
//

#ifndef FLIGHTGEAR_IFCOMMAND_H
#define FLIGHTGEAR_IFCOMMAND_H

#include "ConditionParser.h"

using namespace std;

class IfCommand : public ConditionParser{
    int execute(vector<string>);
    //virtual ~IfCommand();
};


#endif //FLIGHTGEAR_IFCOMMAND_H

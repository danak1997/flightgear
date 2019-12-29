//
// Created by duni on 22/12/2019.
//

#ifndef FLIGHTGEAR_CONDITIONPARSER_H
#define FLIGHTGEAR_CONDITIONPARSER_H


#include "Command.h"
#include <vector>
#include <string>

using namespace std;

class ConditionParser : public Command {
public:
    virtual int execute(vector<string>) = 0;
    //virtual ~ConditionParser();
};


#endif //FLIGHTGEAR_CONDITIONPARSER_H

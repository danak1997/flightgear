//
// Created by duni on 22/12/2019.
//

#ifndef FLIGHTGEAR_IFCOMMAND_H
#define FLIGHTGEAR_IFCOMMAND_H

#include "ConditionParser.h"

using namespace std;

class IfCommand : public ConditionParser{
 public:
    IfCommand(vector<string>,vector<Command>);
    int execute(vector<string>,bool);
    //virtual ~IfCommand();
};


#endif //FLIGHTGEAR_IFCOMMAND_H

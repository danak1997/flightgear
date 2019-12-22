//
// Created by duni on 20/12/2019.
//

#ifndef FLIGHTGEAR_OPENSERVERCOMMAND_H
#define FLIGHTGEAR_OPENSERVERCOMMAND_H

#include "Command.h"
#include <vector>
#include <string>

using namespace std;

class OpenServerCommand : public Command {
public:
    int execute(vector<string>);
    //virtual ~OpenServerCommand();
};


#endif //FLIGHTGEAR_OPENSERVERCOMMAND_H
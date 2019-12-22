//
// Created by duni on 22/12/2019.
//

#ifndef FLIGHTGEAR_CONNECTCOMMAND_H
#define FLIGHTGEAR_CONNECTCOMMAND_H


#include "Command.h"
#include <vector>
#include <string>

using namespace std;

class ConnectCommand : public Command {
private:
    vector<string> params;
public:
    ConnectCommand (vector<string>);
    int execute();
    virtual ~ConnectCommand();
};


#endif //FLIGHTGEAR_CONNECTCOMMAND_H

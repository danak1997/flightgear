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
protected:
    thread threadClient;
public:
    int execute(vector<string>);
    //virtual ~ConnectCommand();
};


#endif //FLIGHTGEAR_CONNECTCOMMAND_H

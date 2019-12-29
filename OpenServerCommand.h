//
// Created by duni on 20/12/2019.
//

#ifndef FLIGHTGEAR_OPENSERVERCOMMAND_H
#define FLIGHTGEAR_OPENSERVERCOMMAND_H

#include "Command.h"
#include <vector>
#include <string>
#include <thread>

using namespace std;

class OpenServerCommand : public Command {
protected:
    thread threadServer;
public:
    int execute(vector<string>);
    // void connectServer(int);
    //virtual ~OpenServerCommand();
};


#endif //FLIGHTGEAR_OPENSERVERCOMMAND_H
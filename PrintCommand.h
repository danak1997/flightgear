//
// Created by duni on 22/12/2019.
//

#ifndef FLIGHTGEAR_PRINTCOMMAND_H
#define FLIGHTGEAR_PRINTCOMMAND_H


#include "Command.h"
#include <vector>
#include <string>

using namespace std;

class PrintCommand : public Command {
private:
    vector<string> params;
public:
    PrintCommand (vector<string>);
    int execute();
    virtual ~PrintCommand();
};

#endif //FLIGHTGEAR_PRINTCOMMAND_H

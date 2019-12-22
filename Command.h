//
// Created by duni on 20/12/2019.
//

#ifndef FLIGHTGEAR_COMMAND_H
#define FLIGHTGEAR_COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {

public:
    virtual int execute(vector<string>) = 0;
    //virtual ~Command() {};

};


#endif //FLIGHTGEAR_COMMAND_H

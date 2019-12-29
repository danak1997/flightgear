//
// Created by duni on 22/12/2019.
//

#ifndef FLIGHTGEAR_PARSER_H
#define FLIGHTGEAR_PARSER_H

#include <vector>
#include <string>
#include <map>
#include "Command.h"

using namespace std;

class Parser {

private:
    vector<string> params;

public:
    Parser(vector<string>);
    void createMap();
    //virtual ~Parser() {};
    void parsering();
};


#endif //FLIGHTGEAR_PARSER_H

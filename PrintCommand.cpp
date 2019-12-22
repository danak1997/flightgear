//
// Created by duni on 22/12/2019.
//

#include <iostream>
#include "PrintCommand.h"

int PrintCommand::execute(vector<string> params) {
    cout << params[1] << endl;
    return 2;
}
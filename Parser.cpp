//
// Created by duni on 22/12/2019.
//

#include <unistd.h>
#include "Parser.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "SetCommand.h"
#include "globalVariables.h"

Parser::Parser(vector<string> params) {
    this->params = params;
}

// This function creates the map of commands
void Parser::createMap() {
    Command *osc = new OpenServerCommand();
    globalVariables::CommandMap.insert({"openDataServer", osc});
    Command *ccc = new ConnectCommand();
    globalVariables::CommandMap.insert({"connectControlClient", ccc});
    Command *dvc = new DefineVarCommand();
    globalVariables::CommandMap.insert({"var", dvc});
    Command *pc = new PrintCommand();
    globalVariables::CommandMap.insert({"Print", pc});
    Command *sc = new SleepCommand();
    globalVariables::CommandMap.insert({"Sleep", sc});
    Command *ic = new IfCommand();
    globalVariables::CommandMap.insert({"if", ic});
    Command *lc = new LoopCommand();
    globalVariables::CommandMap.insert({"while", lc});
}

// This function exectutes each command that is obtained from the txt file
void Parser::parsering() {
    int index = 0;
    Command *c;
    createMap();
    // Go through all of the vector that contains the lines from the file
    while (params.size() > 0) {
        index = 0;
        /* Check if the current command is one of the commands from the map of commands or it is a command that
           assigns a specific variable */
        if (globalVariables::CommandMap.find(params[index]) == globalVariables::CommandMap.end()) {
            c = new SetCommand();
        } else {
            c = globalVariables::CommandMap.at(params[index]);
        }
        if (c != nullptr) {
            index += c->execute(params);
        }

        // Delete the executed command from the lines vector
        vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
        iteratorBegin = params.begin();
        advance(iteratorEnd, index);
        params.erase(iteratorBegin, iteratorEnd);
    }

    close(globalVariables::socketId);
}

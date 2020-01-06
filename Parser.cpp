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

void Parser::createMap() {
    Command* osc = new OpenServerCommand();
    globalVariables::CommandMap.insert({"openDataServer", osc});
    Command* ccc = new ConnectCommand();
    globalVariables::CommandMap.insert({"connectControlClient", ccc});
    Command* dvc = new DefineVarCommand();
    globalVariables::CommandMap.insert({"var", dvc});
    Command* pc = new PrintCommand();
    globalVariables::CommandMap.insert({"Print", pc});
    Command* sc = new SleepCommand();
    globalVariables::CommandMap.insert({"Sleep", sc});
    Command* ic = new IfCommand();
    globalVariables::CommandMap.insert({"if", ic});
    Command* lc = new LoopCommand();
    globalVariables::CommandMap.insert({"while", lc});
}



void Parser::parsering() {
    int index = 0;
    Command *c;
    createMap();
    while (params.size() > 0) {
        index = 0;
        if(globalVariables::CommandMap.find(params[index])==globalVariables::CommandMap.end()){
          c = new SetCommand();
        }
        else {
          c = globalVariables::CommandMap.at(params[index]);
        }
        if (c!= nullptr) {
            index += c->execute(params);
        }
        vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
        iteratorBegin = params.begin();
        advance(iteratorEnd, index);
        params.erase(iteratorBegin, iteratorEnd);
    }

    close(globalVariables::socketId);
}

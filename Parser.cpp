//
// Created by duni on 22/12/2019.
//

#include "Parser.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "SetCommand.h"
#include "Maps.h"

Parser::Parser(vector<string> params) {
    this->params = params;
}

void Parser::createMap() {
    Command* osc = new OpenServerCommand();
    Maps::CommandMap.insert({"openDataServer", osc});
    Command* ccc = new ConnectCommand();
    Maps::CommandMap.insert({"connectControlClient", ccc});
    Command* dvc = new DefineVarCommand();
    Maps::CommandMap.insert({"var", dvc});
    Command* pc = new PrintCommand();
    Maps::CommandMap.insert({"Print", pc});
    Command* sc = new SleepCommand();
    Maps::CommandMap.insert({"Sleep", sc});
    Command* ic = new IfCommand();
    Maps::CommandMap.insert({"if", ic});
    Command* lc = new LoopCommand();
    Maps::CommandMap.insert({"while", lc});
}



void Parser::parsering() {
    int index = 0;
    Command *c;
    createMap();
    while (index < params.size()) {
        index = 0;
        if(Maps::CommandMap[params[index]]==nullptr){
          c = new SetCommand();
        }
        else {
          c = Maps::CommandMap.at(params[index]);
        }
        if (c!= nullptr) {
            index += c->execute(params);
        }
        vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
        iteratorBegin = params.begin();
        advance(iteratorEnd, index);
        params.erase(iteratorBegin, iteratorEnd);
    }

}


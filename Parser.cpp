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


Parser::Parser(vector<string> params) {
    this->params = params;
}

void Parser::createMap() {
    Command* osc = new OpenServerCommand();
    CommandMap.insert({"openDataServer", osc});
    Command* ccc = new ConnectCommand();
    CommandMap.insert({"connectControlClient", ccc});
    Command* dvc = new DefineVarCommand();
    CommandMap.insert({"var", dvc});
    Command* pc = new PrintCommand();
    CommandMap.insert({"Print", pc});
    Command* sc = new SleepCommand();
    CommandMap.insert({"Sleep", sc});
    Command* ic = new IfCommand();
    CommandMap.insert({"if", ic});
    Command* lc = new LoopCommand();
    CommandMap.insert({"while", lc});
}

void Parser::parsering() {
    int index = 0;
    int i;
    createMap();
    while (index < params.size()) {
        index = 0;
        if(CommandMap[params[index]]==nullptr){
          Command *c = new SetCommand();
        }
        else {
          Command *c = CommandMap.at(params[index]);
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
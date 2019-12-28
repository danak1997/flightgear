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

}

void Parser::parsering() {
    int index = 0;
    Command *c;
    createMap();
    while (index < params.size()) {
        index = 0;
        if(CommandMap[params[index]]==nullptr){
          c = new SetCommand();
        }
        else {
          c = CommandMap.at(params[index]);
        }
        if (c!= nullptr) {
            index += c->execute(params, true);
        }
        vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
        iteratorBegin = params.begin();
        advance(iteratorEnd, index);
        params.erase(iteratorBegin, iteratorEnd);
    }

}

int Parser::parseCondition() {
  int index = 0;
  int conditionIndex = 0;
  Command *c;
  auto first = this->params.begin();
  auto last = this->params.begin();
  advance(last, 4);
  vector<string> newVec(first,last);
  vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
  iteratorBegin = params.begin();
  advance(iteratorEnd, 5);
  params.erase(iteratorBegin, iteratorEnd);
  vector<Command> commandVector;
  while (index < params.size()) {
    index = 0;
    if(params[index]=="}"){
      iteratorEnd = params.begin();
      iteratorBegin = params.begin();
      advance(iteratorEnd, 1);
      params.erase(iteratorBegin, iteratorEnd);
      break;
    }
    else if(CommandMap[params[index]]==nullptr){
      c = new SetCommand();
      commandVector.emplace_back(c);
    }
    else {
      c = CommandMap.at(params[index]);
      commandVector.emplace_back(c);
    }
    if (c!= nullptr) {
      index += c->execute(params, false);
    }
    iteratorEnd = params.begin();
    iteratorBegin = params.begin();
    advance(iteratorEnd, index);
    params.erase(iteratorBegin, iteratorEnd);
  }
  if(newVec[0].compare("if")==0){
    Command *ci = new IfCommand(newVec,commandVector);
    conditionIndex = ci->execute(params,true);
  }
  else{
    Command *ci = new LoopCommand(newVec,commandVector);
    conditionIndex = ci->execute(params,true);
  }
  return conditionIndex;
}
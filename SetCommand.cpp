//
// Created by chen96 on 27/12/2019.
//

#include "SetCommand.h"
#include "Maps.h"
#include "ExpressionCalculate.h"
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <algorithm>
#include <unistd.h>

int SetCommand::execute(vector<string> params) {
    Interpreter *i = new Interpreter();
    Expression *e = nullptr;
    try {

        // Remove spaces from the left expression
        string::iterator end_pos = remove(params[2].begin(), params[2].end(), ' ');
        params[2].erase(end_pos, params[2].end());
        // Remove tabs from the left expression
        end_pos = remove(params[2].begin(), params[2].end(), '\t');
        params[2].erase(end_pos, params[2].end());
        // Remove spaces from the right expression
        end_pos = remove(params[0].begin(), params[0].end(), ' ');
        params[0].erase(end_pos, params[0].end());
        // Remove tabs from the right expression
        end_pos = remove(params[0].begin(), params[0].end(), '\t');
        params[0].erase(end_pos, params[0].end());
        e = i->interpret(params[2]);
        // Calculate the left expression
        double answer = e->calculate();
        /* Convert the result of the calculation into float in order to insert to the symbolTable map
           (it's value is defined as a float) */
        float floatAnswer = (float) answer;
        string stringAnswer = to_string(floatAnswer);
        // Insert the calculated value into the symbolTable map
        Maps::symbolTableClientToSim[params[0]].first = floatAnswer;
        // Insert the set command to the simulator according to the wanted syntax
        string setCommandToSim = "set ";
        // Insert the path to the simulator
        setCommandToSim += Maps::symbolTableClientToSim[params[0]].second;
        setCommandToSim += " ";
        setCommandToSim += stringAnswer;
        setCommandToSim += "\r\n";
        const char *setCommandToSend = setCommandToSim.c_str();
        // Send the resulting command to the simulator through the socket
        send(Maps::socketId, setCommandToSend, strlen(setCommandToSend), 0);
        // Delete memory
        delete e;
        delete i;
    } catch (const char *e) {
        if (e != nullptr) {
            delete e;
            delete i;
        }
    }
    return 3;
}

SetCommand::~SetCommand() {
    close(Maps::socketId);
}

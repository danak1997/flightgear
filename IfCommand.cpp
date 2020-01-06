//
// Created by duni on 22/12/2019.
//

#include "IfCommand.h"
#include "globalVariables.h"
#include "SetCommand.h"
#include "ExpressionCalculate.h"
#include <algorithm>

int IfCommand::execute(vector<string> params) {
    int index = 0;
    int returnCount = 0;
    bool booleanCondition = false;
    Command *c;
    auto first = params.begin();
    auto last = params.begin();
    advance(last, 4);
    // Insert the condition of the if statement into a new vector for evaluating it later on
    vector<string> conditionVec(first, last);
    vector<string>::iterator iteratorBegin, iteratorEnd = params.begin();
    iteratorBegin = params.begin();
    advance(iteratorEnd, 5);
    // Delete all the cells that are part of the condition of the if statement from the original vector
    params.erase(iteratorBegin, iteratorEnd);
    // Add the cells of the condition in the if statement into the return value
    returnCount += 5;
    Interpreter *i = new Interpreter();
    Expression *left = nullptr;
    Expression *right = nullptr;
    try {
        // Remove spaces from the left side of the condition
        string::iterator end_pos = remove(conditionVec[1].begin(), conditionVec[1].end(), ' ');
        conditionVec[1].erase(end_pos, conditionVec[1].end());
        // Remove tabs from the left side of the condition
        end_pos = remove(conditionVec[1].begin(), conditionVec[1].end(), '\t');
        // Delete all the cells that are part of the condition of the if statement from the condition vector
        conditionVec[1].erase(end_pos, conditionVec[1].end());
        // Calculate the left side of the condition
        left = i->interpret(conditionVec[1]);
        double answerLeft = left->calculate();
        // Remove spaces from the right side of the condition
        end_pos = remove(conditionVec[3].begin(), conditionVec[3].end(), ' ');
        conditionVec[3].erase(end_pos, conditionVec[3].end());
        // Remove tabs from the right side of the condition
        end_pos = remove(conditionVec[3].begin(), conditionVec[3].end(), '\t');
        conditionVec[3].erase(end_pos, conditionVec[3].end());
        // Calculate the right side of the condition
        right = i->interpret(conditionVec[3]);
        double answerRight = right->calculate();
        // Send the condition of the if statement for evaluation according to the operand
        if (conditionVec[2].compare("<") == 0) {
            if (answerLeft < answerRight) {
                booleanCondition = true;
            }
        } else if (conditionVec[2].compare(">") == 0) {
            if (answerLeft > answerRight) {
                booleanCondition = true;
            }
        } else if (conditionVec[2].compare("<=") == 0) {
            if (answerLeft <= answerRight) {
                booleanCondition = true;
            }
        } else if (conditionVec[2].compare(">=") == 0) {
            if (answerLeft >= answerRight) {
                booleanCondition = true;
            }
        } else if (conditionVec[2].compare("==") == 0) {
            if (abs(answerLeft - answerRight) < 0.0001) {
                booleanCondition = true;
            }
        } else {
            if (abs(answerLeft - answerRight) >= 0.0001) {
                booleanCondition = true;
            }
        }

        // If the condition has evaluated to be true - execute the commands inside it's block
        if (booleanCondition) {
            // Go through all of the commands in the if statement block
            while (index < params.size()) {
                index = 0;
                // Remove spaces
                string::iterator end_pos = remove(params[index].begin(), params[index].end(), ' ');
                params[index].erase(end_pos, params[index].end());
                // Remove tabs
                end_pos = remove(params[index].begin(), params[index].end(), '\t');
                params[index].erase(end_pos, params[index].end());
                // Check if the current line is end of the if statement block
                if (params[index] == "}") {
                    returnCount++;
                    break;
                    /* Check if the current command is one of the commands from the map of commands or it is a command that
                     assigns a specific variable */
                } else if (globalVariables::CommandMap.find(params[index]) == globalVariables::CommandMap.end()) {
                    c = new SetCommand();
                } else {
                    c = globalVariables::CommandMap.at(params[index]);
                }

                // Execute the current command and add it's number of cells to the return value
                if (c != nullptr) {
                    index += c->execute(params);
                    returnCount += index;
                }

                // Delete the current command from the vector
                iteratorEnd = params.begin();
                iteratorBegin = params.begin();
                advance(iteratorEnd, index);
                params.erase(iteratorBegin, iteratorEnd);
            }
            /* If the condition of the if statement has been evaluated to be false,
             * add the if block cells to the return value and don't execute the block commands */
        } else {
            index = 0;
            while (params[index].compare("}") != 0) {
                index++;
            }
            returnCount += index + 1;
        }
    }

        // Delete memory
    catch (const char *e) {
        if (e != nullptr) {
            delete e;
            delete i;
        }
    }

    return returnCount;
}




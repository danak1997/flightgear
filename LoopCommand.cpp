//
// Created by duni on 22/12/2019.
//

#include "LoopCommand.h"
#include "ExpressionCalculate.h"
#include "globalVariables.h"
#include "SetCommand.h"
#include <algorithm>
#include <iostream>

int LoopCommand::execute(vector<string> params) {
    int index = 0;
    int returnCount = 0;
    int currCell = 0;
    Command *c;
    vector<string> block;
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
        // While the condition of the while statement is true - execute the commands of the while block
        while (resultCondition(answerLeft, answerRight, conditionVec[2])) {
            currCell = 0;
            /* Go through all of the commands in the block of the while, and insert them into a new vector that contains
               the commands to be executed in the current iteration (because the values of the different variables are
               being updated in every new iteration of the while command) */
            while (params[currCell].compare("}") != 0) {
                block.emplace_back(params[currCell]);
                currCell++;
            }
            index = 0;
            // Go through all of the commands in the if statement block
            while (block.size() > 0) {
                index = 0;
                bool isCSetCommand = false;
                // Remove spaces
                string::iterator end_pos = remove(block[index].begin(), block[index].end(), ' ');
                block[index].erase(end_pos, block[index].end());
                // Remove tabs
                end_pos = remove(block[index].begin(), block[index].end(), '\t');
                block[index].erase(end_pos, block[index].end());
                /* Check if the current command is one of the commands from the map of commands or it is a command that
                    assigns a specific variable */
                if (globalVariables::CommandMap.find(block[index]) == globalVariables::CommandMap.end()) {
                    c = new SetCommand();
                    isCSetCommand = true;
                } else {
                    c = globalVariables::CommandMap.at(block[index]);
                }

                // Execute the current command and add it's number of cells to the return value
                if (c != nullptr) {
                    index += c->execute(block);
                    if (isCSetCommand) {
                        delete c;
                    }
                }

                // Delete the current command from the block commands vector
                iteratorEnd = block.begin();
                iteratorBegin = block.begin();
                advance(iteratorEnd, index);
                block.erase(iteratorBegin, iteratorEnd);
            }

            // Calculate both of the sides of the while condition
            left = i->interpret(conditionVec[1]);
            answerLeft = left->calculate();
            right = i->interpret(conditionVec[3]);
            answerRight = right->calculate();
        }
        index = 0;
        // add the if block cells to the return value
        while (params[index].compare("}") != 0) {
            index++;
        }
        returnCount += index + 1;
    }

        // Delete memory
    catch (const char *e) {
        if (e != nullptr) {
            cout << "no" << endl;
            delete e;
            delete i;
        }
    }

    return returnCount;
}

// This function is evaluating the condition of the while command
bool LoopCommand::resultCondition(double answerLeft, double answerRight, string op) {
    if (op.compare("<") == 0) {
        return (answerLeft < answerRight);
    } else if (op.compare(">") == 0) {
        return (answerLeft > answerRight);
    } else if (op.compare("<=") == 0) {
        return (answerLeft <= answerRight);
    } else if (op.compare(">=") == 0) {
        return (answerLeft >= answerRight);
    } else if (op.compare("==") == 0) {
        return (abs(answerLeft - answerRight) < 0.0001);
    } else {
        return (abs(answerLeft - answerRight) >= 0.0001);
    }
}


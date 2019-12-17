//
// Created by duni on 17/12/2019.
//
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <regex.h>
#include <regex>
#include "lexer.h"
using namespace std;

class Lexer {

public:

    bool doesParanthesisExist (string line) {
        regex parenthesis ("((\\().*(\\)))");
        int count = distance(sregex_iterator (line.begin(), line.end(), parenthesis), sregex_iterator());
        return count != 0;
    }

    bool doesIfOrWhileExistAndSpace (string line) {
        regex parenthesis ("(while|if)( ).*");
        int count = distance(sregex_iterator (line.begin(), line.end(), parenthesis), sregex_iterator());
        return count != 0;
    }

    bool doesESExist (string line) {
        regex parenthesis ("(\\<\\=)");
        int count = distance(sregex_iterator (line.begin(), line.end(), parenthesis), sregex_iterator());
        return count != 0;
    }

    bool doesEGExist (string line) {
        regex parenthesis ("(\\>\\=)");
        int count = distance(sregex_iterator (line.begin(), line.end(), parenthesis), sregex_iterator());
        return count != 0;
    }

    bool doesEEExist (string line) {
        regex parenthesis ("(\\=\\=)");
        int count = distance(sregex_iterator (line.begin(), line.end(), parenthesis), sregex_iterator());
        return count != 0;
    }

    bool doesNEExist (string line) {
        regex parenthesis ("(\\!\\=)");
        int count = distance(sregex_iterator (line.begin(), line.end(), parenthesis), sregex_iterator());
        return count != 0;
    }

    bool doesIfOrWhileExistAndPar (string line) {
        regex parenthesis ("(while|if)(\\().*");
        int count = distance(sregex_iterator (line.begin(), line.end(), parenthesis), sregex_iterator());
        return count != 0;
    }

    bool doesDelimExist (string line, char delim) {
        char currChar;
        int i;
        for (i = 0; i < line.length(); i++) {
            currChar = line[i];
            if (currChar == delim) {
                return true;
            }
            return false;
        }
    }

    void lexer(string fileName) {
        int i;
        vector<string> strArray;
        string line;
        char *wordToPushPartOne;
        char *wordToPushPartTwo;
        char *wordToPushPartThree;
        char *wordToPushPartFour;
        bool isPar = false;
        bool isDDigit = false;
        string delim;

        ifstream in_file{fileName, std::ios::in};
        if (!in_file.is_open()) {
            throw "Cannot open file";
        }

        while (getline(in_file, line)) {
            char lineStrTok[line.length() + 1];
            strcpy(lineStrTok, line.c_str());

            if (doesIfOrWhileExistAndSpace(line) || doesIfOrWhileExistAndPar(line)) {
                if (doesIfOrWhileExistAndSpace(line)) {
                    strArray.emplace_back(strtok(lineStrTok, " "));
                } else {
                    isPar = true;
                    strArray.emplace_back(strtok(lineStrTok, "("));
                }
                if (doesDelimExist(line, '>')) {
                    wordToPushPartOne = strtok(NULL, ">");
                    delim = ">";
                } else if (doesDelimExist(line, '<')) {
                    wordToPushPartOne = strtok(NULL, "<");
                    delim = "<";
                } else if (doesESExist(line)) {
                    wordToPushPartOne = strtok(NULL, "<=");
                    delim = "<=";
                    isDDigit = true;
                } else if (doesEGExist(line)) {
                    wordToPushPartOne = strtok(NULL, ">=");
                    delim = ">=";
                    isDDigit = true;
                } else if (doesEEExist(line)) {
                    wordToPushPartOne = strtok(NULL, "==");
                    delim = "==";
                    isDDigit = true;
                } else if (doesNEExist(line)) {
                    wordToPushPartOne = strtok(NULL, "!=");
                    delim = "!=";
                    isDDigit = true;
                }
                strArray.emplace_back(wordToPushPartOne);
                strArray.emplace_back(delim);
                wordToPushPartTwo = strtok(NULL, "{");
                if (isDDigit) {
                    for (i = 1; i < strlen(wordToPushPartTwo); i++) {
                        wordToPushPartTwo[i - 1] = wordToPushPartTwo[i];
                    }
                }
                if (!isPar) {
                    strArray.emplace_back(wordToPushPartTwo);
                } else {
                    wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
                    strArray.emplace_back(wordToPushPartTwo);
                }

                strArray.emplace_back("{");
            }









//            if (doesParanthesisExist(line)) {
//                wordToPushPartOne = strtok(lineStrTok, "(");
//                wordToPushPartTwo = strtok(NULL, ")");
//                cout << wordToPushPartOne << endl;
//                cout << wordToPushPartTwo << endl;
//            } if (doesEqualExist(wordToPushPartOne, '=')) {
//                wordToPushPartThree = strtok(lineStrTok, "=");
//                wordToPushPartFour = strtok(NULL, "=");
//                cout << wordToPushPartThree << endl;
//                cout << wordToPushPartFour << endl;
//            } if (doesEqualExist(wordToPushPartTwo, '=')) {
//                wordToPushPartThree = strtok(lineStrTok, "=");
//                wordToPushPartFour = strtok(NULL, "=");
//                cout << wordToPushPartThree << endl;
//                cout << wordToPushPartFour << endl;
//            }
//
//
//        }

        }
    }

};


//
// Created by duni on 17/12/2019.
//
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <regex>
#include "lexer.h"
using namespace std;

class Lexer {

 public:

  bool doesCommaExist(string line) {
    regex parenthesis("(.*,.*)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesEqualExist(string line) {
    regex parenthesis("(.*\\=.*)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesVarExistAndArrow(string line) {
    regex parenthesis("(var.*(->|<-).*)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesVarExistAndArrowRight(string line) {
    regex parenthesis("(var.*->.*)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesVarExistAndEqual(string line) {
    regex parenthesis("(var.*\\=.*)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesParanthesisExist(string line) {
    regex parenthesis("((\\().*(\\)))");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesIfOrWhileExistAndSpace(string line) {
    regex parenthesis("(while|if)( )(?!\\().*");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesESExist(string line) {
    regex parenthesis("(\\<\\=)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesEGExist(string line) {
    regex parenthesis("(\\>\\=)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesEEExist(string line) {
    regex parenthesis("(\\=\\=)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesNEExist(string line) {
    regex parenthesis("(\\!\\=)");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesIfOrWhileExistAndPar(string line) {
    regex parenthesis("(while|if)( )?(\\().*");
    int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
    return count != 0;
  }

  bool doesDelimExist(string line, char delim) {
    char currChar;
    int i;
    for (i = 0; i < line.length(); i++) {
      currChar = line[i];
      if (currChar == delim) {
        return true;
      }
    }
    return false;
  }

  vector<string> lexer(string fileName) {
    int i;
    vector<string> strArray;
    string line;
    char *wordToPushPartOne;
    char *wordToPushPartTwo;
    char *wordToPushPartThree;
    char *wordToPushPartFour;
    bool isPar = false;
    bool isDDigit = false;
    bool isArrowLeft = false;
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
          string::iterator end_pos = remove(line.begin(), line.end(), ' ');
          line.erase(end_pos, line.end());
          end_pos = remove(line.begin(), line.end(), '\t');
          line.erase(end_pos, line.end());
          lineStrTok[line.length() + 1];
          strcpy(lineStrTok, line.c_str());
          isPar = true;
          strArray.emplace_back(strtok(lineStrTok, "("));
        }
        if (doesESExist(line)) {
          wordToPushPartOne = strtok(nullptr, "<=");
          delim = "<=";
          isDDigit = true;
        } else if (doesEGExist(line)) {
          wordToPushPartOne = strtok(nullptr, ">=");
          delim = ">=";
          isDDigit = true;
        } else if (doesEEExist(line)) {
          wordToPushPartOne = strtok(nullptr, "==");
          delim = "==";
          isDDigit = true;
        } else if (doesNEExist(line)) {
          wordToPushPartOne = strtok(nullptr, "!=");
          delim = "!=";
          isDDigit = true;
        } else if (doesDelimExist(line, '>')) {
          wordToPushPartOne = strtok(nullptr, ">");
          delim = ">";
          isDDigit = false;
        } else if (doesDelimExist(line, '<')) {
          wordToPushPartOne = strtok(nullptr, "<");
          delim = "<";
          isDDigit = false;
        }
        strArray.emplace_back(wordToPushPartOne);
        strArray.emplace_back(delim);
        wordToPushPartTwo = strtok(nullptr, "{");
        if(isPar) {
          if (isDDigit) {
            for (i = 1; i < strlen(wordToPushPartTwo); i++) {
              wordToPushPartTwo[i - 1] = wordToPushPartTwo[i];
            }

            wordToPushPartTwo[strlen(wordToPushPartTwo) - 2] = '\0';
          } else {
            wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
          }
        } else{
          *remove(wordToPushPartTwo, wordToPushPartTwo + strlen(wordToPushPartTwo), ' ') = 0;
          if (isDDigit) {
            for (i = 1; i < strlen(wordToPushPartTwo); i++) {
              wordToPushPartTwo[i - 1] = wordToPushPartTwo[i];
            }

            wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
          }
        }
        strArray.emplace_back(wordToPushPartTwo);
        isPar = false;
        strArray.emplace_back("{");
      } else if (doesVarExistAndEqual(line)) {
        wordToPushPartOne = strtok(lineStrTok, " ");
        strArray.emplace_back(wordToPushPartOne);
        wordToPushPartTwo = strtok(nullptr, "=");
        strArray.emplace_back(wordToPushPartTwo);
        strArray.emplace_back("=");
        wordToPushPartThree = strtok(nullptr, "\n");
        strArray.emplace_back(wordToPushPartThree);
      } else if (doesVarExistAndArrow(line)) {
        wordToPushPartOne = strtok(lineStrTok, " ");
        strArray.emplace_back(wordToPushPartOne);
        if (doesVarExistAndArrowRight(line)) {
          wordToPushPartTwo = strtok(nullptr, "->");
        } else {
          wordToPushPartTwo = strtok(nullptr, "<-");
          isArrowLeft = true;
        }
        strArray.emplace_back(wordToPushPartTwo);
        if (isArrowLeft) {
          strArray.emplace_back("<-");
        } else {
          strArray.emplace_back("->");
        }
        isArrowLeft = false;
        wordToPushPartThree = strtok(nullptr, "(");
        for (i = 1; i < strlen(wordToPushPartThree); i++) {
          wordToPushPartThree[i - 1] = wordToPushPartThree[i];
        }
        wordToPushPartThree[strlen(wordToPushPartThree) - 1] = '\0';
        strArray.emplace_back(wordToPushPartThree);
        wordToPushPartFour = strtok(nullptr, ")");
        strArray.emplace_back(wordToPushPartFour);
      } else if (doesEqualExist(line)) {
        wordToPushPartOne = strtok(lineStrTok, "=");
        strArray.emplace_back(wordToPushPartOne);
        strArray.emplace_back("=");
        wordToPushPartTwo = strtok(nullptr, "\n");
        strArray.emplace_back(wordToPushPartTwo);
      } else if (doesParanthesisExist(line)) {
        wordToPushPartOne = strtok(lineStrTok, "(");
        strArray.emplace_back(wordToPushPartOne);
        if (doesCommaExist(line)) {
          wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
          wordToPushPartTwo = strtok(nullptr, ",");
          while (wordToPushPartTwo) {
            strArray.emplace_back(wordToPushPartTwo);
            wordToPushPartTwo = strtok(nullptr, ",");
          }
        } else {
          wordToPushPartTwo = strtok(nullptr, ")");
          strArray.emplace_back(wordToPushPartTwo);
        }
      } else {
        strArray.emplace_back(line);
      }
    }
    return strArray;
  }
};


//
// Created by duni on 17/12/2019.
//
#include <iostream>
#include <fstream>
#include <regex>
#include "Lexer.h"

// The function returns true if a comma exists in the line
static bool doesCommaExist(string line) {
  regex parenthesis("(.*,.*)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if a comma exists between quotation marks in the line
static bool doesCommaExistBetweenQuotationMarks(string line) {
  regex parenthesis("(.*\".*,.*\".*)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "=" exists in the line
static bool doesEqualExist(string line) {
  regex parenthesis("(.*\\=.*)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "Var" exists with an arrow
static bool doesVarExistAndArrow(string line) {
  regex parenthesis("(var.*(->|<-).*)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "Var" exists with right arrow
static bool doesVarExistAndArrowRight(string line) {
  regex parenthesis("(var.*->.*)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "Var" exists with "="
static bool doesVarExistAndEqual(string line) {
  regex parenthesis("(var.*\\=.*)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if parenthesis exist in the line
static bool doesParenthesisExist(string line) {
  regex parenthesis("((\\().*(\\)))");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "While" or "If" exists with space
static bool doesIfOrWhileExistAndSpace(string line) {
  regex parenthesis("(while|if)( )(?!\\().*");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "<=" exists in the line
static bool doesESExist(string line) {
  regex parenthesis("(\\<\\=)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if ">=" exists in the line
static bool doesEGExist(string line) {
  regex parenthesis("(\\>\\=)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "==" exists in the line
static bool doesEEExist(string line) {
  regex parenthesis("(\\=\\=)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "!=" exists in the line
static bool doesNEExist(string line) {
  regex parenthesis("(\\!\\=)");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if "While" or "If" exists with parenthesis
static bool doesIfOrWhileExistAndPar(string line) {
  regex parenthesis("(while|if)( )?(\\().*");
  int count = distance(sregex_iterator(line.begin(), line.end(), parenthesis), sregex_iterator());
  return count != 0;
}

// The function returns true if the specified delimiter exists in the line
static bool doesDelimExist(string line, char delim) {
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

// The function of the Lexer that do lexical Analysis of the text file
vector<string> Lexer::lexicalAnalysis(string fileName) {
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
  ifstream in_file{fileName, ios::in};
  if (!in_file.is_open()) {
    throw "Cannot open file";
  }
  // reads line by line from the file
  while (getline(in_file, line)) {
    // creates char* from the line string
    char lineStrTok[line.length() + 1];
    //copy the string to the char*
    strcpy(lineStrTok, line.c_str());
    // checks if the line contains "while" of "if" with space or parenthesis
    if (doesIfOrWhileExistAndSpace(line) || doesIfOrWhileExistAndPar(line)) {
      // checks if "While" or "If" exists with space
      if (doesIfOrWhileExistAndSpace(line)) {
        // push "while" or "if" to the vector
        strArray.emplace_back(strtok(lineStrTok, " "));
      } else {
        // remove spaces from the line
        string::iterator end_pos = remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());
        // remove tabs from the line
        end_pos = remove(line.begin(), line.end(), '\t');
        line.erase(end_pos, line.end());
        // initialize the char*
        lineStrTok[line.length() + 1];
        strcpy(lineStrTok, line.c_str());
        isPar = true;
        // push "(" to the vector
        strArray.emplace_back(strtok(lineStrTok, "("));
      }
      // checks the possible conditions exists in "While" or "If" statement
      if (doesESExist(line)) {
        wordToPushPartOne = strtok(nullptr, "<=");
        delim = "<=";
        // The delimiter has 2 chars
        isDDigit = true;
      } else if (doesEGExist(line)) {
        wordToPushPartOne = strtok(nullptr, ">=");
        delim = ">=";
        // The delimiter has 2 chars
        isDDigit = true;
      } else if (doesEEExist(line)) {
        wordToPushPartOne = strtok(nullptr, "==");
        delim = "==";
        // The delimiter has 2 chars
        isDDigit = true;
      } else if (doesNEExist(line)) {
        wordToPushPartOne = strtok(nullptr, "!=");
        delim = "!=";
        // The delimiter has 2 chars
        isDDigit = true;
      } else if (doesDelimExist(line, '>')) {
        wordToPushPartOne = strtok(nullptr, ">");
        delim = ">";
        // The delimiter has 1 chars
        isDDigit = false;
      } else if (doesDelimExist(line, '<')) {
        wordToPushPartOne = strtok(nullptr, "<");
        delim = "<";
        // The delimiter has 1 chars
        isDDigit = false;
      }
      // push the left expression to the vector
      strArray.emplace_back(wordToPushPartOne);
      // push the delimiter to the vector
      strArray.emplace_back(delim);
      // remove "{" from the left expression
      wordToPushPartTwo = strtok(nullptr, "{");
      // checks if the right expression has parenthesis
      if (isPar) {
        // checks if the delimiter has 2 chars
        if (isDDigit) {
          // remove the extra char of the delimiter from the right expression
          for (i = 1; i < strlen(wordToPushPartTwo); i++) {
            wordToPushPartTwo[i - 1] = wordToPushPartTwo[i];
          }
          // remove ")" from the end of the right expression
          wordToPushPartTwo[strlen(wordToPushPartTwo) - 2] = '\0';
        } else {
          // remove ")" from the end of the right expression
          wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
        }
      } else {
        // remove spaces from the right expression
        *remove(wordToPushPartTwo, wordToPushPartTwo + strlen(wordToPushPartTwo), ' ') = 0;
        // checks if the delimiter has 2 chars
        if (isDDigit) {
          // remove the extra char of the delimiter from the right expression
          for (i = 1; i < strlen(wordToPushPartTwo); i++) {
            wordToPushPartTwo[i - 1] = wordToPushPartTwo[i];
          }
          wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
        }
      }
      // push the right expression the the vector
      strArray.emplace_back(wordToPushPartTwo);
      isPar = false;
      strArray.emplace_back("{");
      // checks if "var" exists with "="
    } else if (doesVarExistAndEqual(line)) {
      // splits with space
      wordToPushPartOne = strtok(lineStrTok, " ");
      // push "var" to the vector
      strArray.emplace_back(wordToPushPartOne);
      // split with "="
      wordToPushPartTwo = strtok(nullptr, "=");
      // push the variable to the vector
      strArray.emplace_back(wordToPushPartTwo);
      strArray.emplace_back("=");
      // split with "\n"
      wordToPushPartThree = strtok(nullptr, "\n");
      // push the right expression to the vector
      strArray.emplace_back(wordToPushPartThree);
      // checks if "var" exists with an arrow
    } else if (doesVarExistAndArrow(line)) {
      // splits with space
      wordToPushPartOne = strtok(lineStrTok, " ");
      strArray.emplace_back(wordToPushPartOne);
      // checks if "var" exists with "->"
      if (doesVarExistAndArrowRight(line)) {
        wordToPushPartTwo = strtok(nullptr, "->");
      } else {
        wordToPushPartTwo = strtok(nullptr, "<-");
        isArrowLeft = true;
      }
      // push the variable name to the vector
      strArray.emplace_back(wordToPushPartTwo);
      if (isArrowLeft) {
        strArray.emplace_back("<-");
      } else {
        strArray.emplace_back("->");
      }
      isArrowLeft = false;
      // splits with "("
      wordToPushPartThree = strtok(nullptr, "(");
      // remove the extra char of the arrow from "sim"
      for (i = 1; i < strlen(wordToPushPartThree); i++) {
        wordToPushPartThree[i - 1] = wordToPushPartThree[i];
      }
      wordToPushPartThree[strlen(wordToPushPartThree) - 1] = '\0';
      // push "sim" to the vector
      strArray.emplace_back(wordToPushPartThree);
      // gets the path in the sim
      wordToPushPartFour = strtok(nullptr, "");
      // remove the ")"
      wordToPushPartFour[strlen(wordToPushPartFour) - 1] = '\0';
      // push the path to the vector
      strArray.emplace_back(wordToPushPartFour);
      // checks if "=" exists and quotation marks does not exist
    } else if ((doesEqualExist(line)) && (!doesDelimExist(line, '"'))) {
      wordToPushPartOne = strtok(lineStrTok, "=");
      // push left expression to the vector
      strArray.emplace_back(wordToPushPartOne);
      strArray.emplace_back("=");
      wordToPushPartTwo = strtok(nullptr, "\n");
      // push the right expression to the vector
      strArray.emplace_back(wordToPushPartTwo);
      // checks if parenthesis exist
    } else if (doesParenthesisExist(line)) {
      wordToPushPartOne = strtok(lineStrTok, "(");
      strArray.emplace_back(wordToPushPartOne);
      // checks if comma exists and it is not between quotation marks
      if (doesCommaExist(line) && (!doesCommaExistBetweenQuotationMarks(line))) {
        // removes ")"
        wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
        wordToPushPartTwo = strtok(nullptr, ",");
        // splits with comma
        while (wordToPushPartTwo) {
          strArray.emplace_back(wordToPushPartTwo);
          wordToPushPartTwo = strtok(nullptr, ",");
        }
      } else {
        wordToPushPartTwo = strtok(nullptr, "");
        // removes ")"
        wordToPushPartTwo[strlen(wordToPushPartTwo) - 1] = '\0';
        strArray.emplace_back(wordToPushPartTwo);
      }
    } else {
      strArray.emplace_back(line);
    }
  }
  return strArray;
}
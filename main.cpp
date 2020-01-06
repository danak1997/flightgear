#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "globalVariables.h"

int main(int argc, char *argv[])
{
    Lexer* l = new Lexer();
    Parser* p = new Parser(l->lexicalAnalysis(argv[1]));
    p->parsering();

    return 0;
}

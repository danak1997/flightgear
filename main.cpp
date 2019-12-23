#include <iostream>
#include "lexer.cpp"
#include "lexer.h"
#include "Parser.h"

int main()
{
    Lexer* l = new Lexer();
    Parser* p = new Parser(l->lexer("/home/chen96/Documents/GitHub/flightgear/fly.txt"));
    p->parsering();

    return 0;
}

#include <iostream>
#include "lexer.cpp"
#include "lexer.h"
#include "Parser.h"

int main()
{
    Lexer* l = new Lexer();
    Parser* p = new Parser(l->lexer("fly.txt"));
    p->parsering();
    while(1) {}

    return 0;
}

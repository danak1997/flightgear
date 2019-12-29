#include <iostream>
#include "lexer.cpp"
#include "lexer.h"
#include "Parser.h"
#include "Maps.h"
int main()
{
    Lexer* l = new Lexer();
    Parser* p = new Parser(l->lexer("fly.txt"));
    p->parsering();

    return 0;
}

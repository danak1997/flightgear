#include <iostream>
#include "lexer.cpp"
#include "lexer.h"

int main()
{
    Lexer* l = new Lexer();

    l->lexer("/home/duni/Documents/GitHub/flightgear/fly.txt");

    return 0;
}

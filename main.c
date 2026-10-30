#include <stdio.h>
#include "lexer.h"

int main ()
{
    printf("===============================================\n");
    printf("            C LEXICAL ANALYZER\n");
    printf("===============================================\n");

    analyzerFile("input.c");

    return 0;
}
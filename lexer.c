#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

const char *keywords[] =
{
 "auto",
 "break",
 "case",
 "char",
 "const",
 "continue",
 "default",
 "do",
 "double",
 "else",
 "enum",
 "extern",
 "float",
 "for",
 "goto",
 "if",
 "int",
 "long",
 "register",
 "return",
 "short",
 "signed",
 "sizeof",
 "static",
 "struct",
 "switch",
 "typedef",
 "union",
 "unsigned",
 "void",
 "volatile",
 "while"
};

int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

int isKeyword(const char *word)
{
    for(int i = 0; i < keywordCount; i++)
    {
        if(strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int isOperator(char ch)
{
    char operators[] =
    {
        '+', '-', '*', '/', '%',
        '=', '<', '>', '!', '&',
        '|'
    };

    for(int i = 0; operators[i] != '\0'; i++)
    {
        if(ch == operators[i])
        {
            return 1;
        }
    }

    return 0;
}

int isDelimiter(char ch)
{
    char delimiters[] =
    {
        '(', ')',
        '{', '}',
        '[', ']',
        ';', ','
    };

    for(int i = 0; delimiters[i] != '\0'; i++)
    {
        if(ch == delimiters[i])
        {
            return 1;
        }
    }

    return 0;
}

void analyzerFile(const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    char ch;

    while((ch = fgetc(fp)) != EOF)
    {
        if(isspace(ch))
        {
            continue;
        }

        /* Identifier or Keyword */
        if(isalpha(ch) || ch == '_')
        {
            char word[100];
            int i = 0;

            word[i++] = ch;

            while((ch = fgetc(fp)) != EOF &&
                  (isalnum(ch) || ch == '_'))
            {
                word[i++] = ch;
            }

            word[i] = '\0';

            if(ch != EOF)
            {
                ungetc(ch, fp);
            }

            if(isKeyword(word))
            {
                printf("%-20s -> KEYWORD\n", word);
            }
            else
            {
                printf("%-20s -> IDENTIFIER\n", word);
            }

            continue;
        }

        /* Constant */
        if(isdigit(ch))
        {
            char number[100];
            int i = 0;

            number[i++] = ch;

            while((ch = fgetc(fp)) != EOF &&
                  (isdigit(ch) || ch == '.'))
            {
                number[i++] = ch;
            }

            number[i] = '\0';

            if(ch != EOF)
            {
                ungetc(ch, fp);
            }

            printf("%-20s -> CONSTANT\n", number);

            continue;
        }

        if(ch =='"')
        {
            char str[200];
            int i = 0;

            str[i++] = ch;

            while((ch = fgetc(fp)) != EOF && ch != '"')
            {
                str[i++] = ch;
            }

            if(ch == '"')
            {
                str[i++] = ch;
            }

            str[i] = '\0';

            printf("%-20s -> STRING\n", str);

            continue;
        }

        /* Operator */
        if(isOperator(ch))
        {
            char op[3];

            op[0] = ch;
            op[1] = '\0';

            char next = fgetc(fp);

            if((ch == '=' && next == '=') ||
               (ch == '!' && next == '=') ||
               (ch == '<' && next == '=') ||
               (ch == '>' && next == '=') ||
               (ch == '&' && next == '&') ||
               (ch == '|' && next == '|') ||
               (ch == '+' && next == '+') ||
               (ch == '-' && next == '-'))
            {
                op[1] = next;
                op[2] = '\0';
            }
            else
            {
                if(next != EOF)
                {
                    ungetc(next, fp);
                }
            }

            printf("%-20s -> OPERATOR\n", op);

            continue;
        }

        /* Delimiter */
        if(isDelimiter(ch))
        {
            printf("%-20c -> DELIMITER\n", ch);

            continue;
        }

        /* Invalid Token */
        printf("%-20c -> INVALID TOKEN\n", ch);
    }

    fclose(fp);
}
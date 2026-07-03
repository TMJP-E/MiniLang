#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

#define loadLookup(count)                \
    currentLookAhead = count - 1;        \
    for (size_t i = 0; i < 6; i++)       \
    {                                    \
        keyword[i] = '\0';               \
    }                                    \
    for (size_t i = 0; i < (count); i++) \
    {                                    \
        keyword[i] = input[pos - 1 + i]; \
    }

char *input;
int pos = 0;
char keyword[6] = "";
int keywordLookAhead = 0;
int currentLookAhead = 0;
char lookAhead = 0;

Token getNextToken()
{

    while (input[pos] == ' ')
        pos++;

    while (input[pos] == '\n')
        pos++;

    while (input[pos] == '\t')
        pos++;

    if (input[pos] == '\0')
        return (Token){TOKEN_EOF, 0};

    if (isdigit(input[pos]))
    {
        int value = 0;

        while (isdigit(input[pos]))
        {
            value = value * 10 + (input[pos] - '0');
            pos++;
        }

        return (Token){TOKEN_NUMBER, value};
    }

    char c = input[pos++];
    char next = input[pos];

    switch (c)
    {
    case '+':
        return (Token){TOKEN_PLUS, 0};
    case '-':
        return (Token){TOKEN_MINUS, 0};
    case '*':
        return (Token){TOKEN_MULT, 0};
    case '/':
        return (Token){TOKEN_DIV, 0};
    case '=':
        if (next == '=')
        {
            pos++;
            return (Token){TOKEN_EQ, 0};
        }
        return (Token){TOKEN_ASSIGN, 0};
    case '!':
        if (next == '=')
        {
            pos++;
            return (Token){TOKEN_NEQ, 0};
        }
        return (Token){TOKEN_INVALID, 0};
    case '(':
        return (Token){TOKEN_LPAREN, 0};
    case ')':
        return (Token){TOKEN_RPAREN, 0};
    case '{':
        return (Token){TOKEN_LBRACE, 0};
    case '}':
        return (Token){TOKEN_RBRACE, 0};
    case '<':
        if (next == '=')
        {
            pos++;
            return (Token){TOKEN_LTE, 0};
        }
        return (Token){TOKEN_LT, 0};
    case '>':
        if (next == '=')
        {
            pos++;
            return (Token){TOKEN_GTE, 0};
        }
        return (Token){TOKEN_GT, 0};
    case '"':
        return (Token){TOKEN_QUOTE, 0};
    case ';':
        return (Token){TOKEN_SEMICOLON, 0};
    case 'b':
        loadLookup(6);
        if (strcmp(keyword, "begin\n") == 0)
        {
            pos += currentLookAhead;
            return (Token){TOKEN_BEGIN, 0};
        }
        break;
    case 'e':
        loadLookup(4);
        if (strcmp(keyword, "end\n") == 0)
        {
            pos += currentLookAhead;
            return (Token){TOKEN_END, 0};
        }
        if (strcmp(keyword, "else") == 0)
        {
            keywordLookAhead = 0;
            lookAhead = input[pos + keywordLookAhead + currentLookAhead];
            while (lookAhead == ' ' || lookAhead == '\n' || lookAhead == '\t')
            {
                keywordLookAhead++;
                lookAhead = input[pos + keywordLookAhead + currentLookAhead];
            }
            if (input[pos + keywordLookAhead + currentLookAhead] == '{')
            {
                pos += currentLookAhead;
                return (Token){TOKEN_ELSE, 0};
            }
        }
        break;
    case 'i':
        if (next == 'f')
        {
            keywordLookAhead = 1;
            lookAhead = input[pos + keywordLookAhead];
            while (lookAhead == ' ' || lookAhead == '\n' || lookAhead == '\t')
            {
                keywordLookAhead++;
                lookAhead = input[pos + keywordLookAhead];
            }
            if (input[pos + keywordLookAhead] == '(')
            {
                pos++;
                return (Token){TOKEN_IF, 0};
            }
        }
        break;
    case 'p':
        loadLookup(5);
        if (strcmp(keyword, "print") == 0)
        {
            keywordLookAhead = 0;
            lookAhead = input[pos + keywordLookAhead + currentLookAhead];
            while (lookAhead == ' ' || lookAhead == '\n' || lookAhead == '\t')
            {
                keywordLookAhead++;
                lookAhead = input[pos + keywordLookAhead + currentLookAhead];
            }
            if (input[pos + keywordLookAhead + currentLookAhead] == '(')
            {
                pos += currentLookAhead;
                return (Token){TOKEN_PRINT, 0};
            }
        }
        break;
    case 'w':
        loadLookup(5);
        if (strcmp(keyword, "while") == 0)
        {
            keywordLookAhead = 0;
            lookAhead = input[pos + keywordLookAhead + currentLookAhead];
            while (lookAhead == ' ' || lookAhead == '\n' || lookAhead == '\t')
            {
                keywordLookAhead++;
                lookAhead = input[pos + keywordLookAhead + currentLookAhead];
            }
            if (input[pos + keywordLookAhead + currentLookAhead] == '(')
            {
                pos += currentLookAhead;
                return (Token){TOKEN_WHILE, 0};
            }
        }
        break;
    default:
        break;
    }

    return (Token){TOKEN_INVALID, 0};
}

// Pruebas
void main()
{
    Token token;
    input = "if(1)\n";
    while (token.type != TOKEN_EOF)
    {
        token = getNextToken();
        printf("%d\n", token);
    }
}
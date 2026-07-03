#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOKEN_BEGIN,
    TOKEN_END,
    TOKEN_ID,
    TOKEN_NUMBER,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_PRINT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_ASSIGN,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LT,
    TOKEN_LTE,
    TOKEN_GT,
    TOKEN_GTE,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_STRING,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_INVALID,
} TokenType;

typedef struct
{
    TokenType type;
    union
    {
        int number;
        char *name;
    };

} Token;

extern char *input;
extern int pos;

Token getNextToken();

#endif

/*
0 - TOKEN_BEGIN,
1 - TOKEN_END,
2 - TOKEN_ID,
3 - TOKEN_NUMBER,
4 - TOKEN_IF,
5 - TOKEN_ELSE,
6 - TOKEN_WHILE,
7 - TOKEN_PRINT,
8 - TOKEN_PLUS,
9 - TOKEN_MINUS,
10 - TOKEN_MULT,
11 - TOKEN_DIV,
12 - TOKEN_ASSIGN,
13 - TOKEN_LPAREN,
14 - TOKEN_RPAREN,
15 - TOKEN_LBRACE,
16 - TOKEN_RBRACE,
17 - TOKEN_LT,
18 - TOKEN_LTE,
19 - TOKEN_GT,
20 - TOKEN_GTE,
21 - TOKEN_EQ,
22 - TOKEN_NEQ,
23 - TOKEN_STRING,
24 - TOKEN_SEMICOLON,
25 - TOKEN_EOF,
26 - TOKEN_INVALID,
*/
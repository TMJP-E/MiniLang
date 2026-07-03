#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

typedef struct
{
    const char **symbols;
    size_t count;
    size_t capacity;
} Identifiers;

void append(Identifiers *list, char *name)
{
    if (list->count >= list->capacity)
    {
        if (list->capacity == 0)
        {
            list->capacity = 32;
        }
        list->capacity *= 2;
    }
    list->symbols = realloc(list->symbols, list->capacity * sizeof(*list->symbols));
    list->symbols[list->count++] = name;
}

int find(Identifiers *list, char *name)
{
    for (size_t i = 0; i < list->count; i++)
    {
        if (strcmp(name, list->symbols[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

Token current;
Identifiers ids;

void error(TokenType expected)
{
    printf("Error sintactico - Esperado: %d. | Recibido: %d.\n", expected, current.type);
    exit(1);
}

void match(TokenType expected)
{
    if (current.type == expected)
        current = getNextToken();
    else
        error(expected);
}

void A()
{
    match(TOKEN_BEGIN);
    B();
    match(TOKEN_END);
}
void B()
{
    if (current.type == TOKEN_ID || current.type == TOKEN_IF || current.type == TOKEN_WHILE || current.type == TOKEN_PRINT)
    {
        C();
        B();
    }
}
void C()
{
    if (current.type == TOKEN_ID)
    {
        W();
    }
    else if (current.type == TOKEN_IF)
    {
        X();
    }
    else if (current.type == TOKEN_WHILE)
    {
        Y();
    }
    else if (current.type == TOKEN_PRINT)
    {
        Z();
    }
    else
    {
        error(TOKEN_INVALID);
    }
}
void W()
{
    char *name = current.name;
    match(TOKEN_ID);
    match(TOKEN_ASSIGN);
    E();
    match(TOKEN_SEMICOLON);
    append(&ids, name);
}
void X()
{
    match(TOKEN_IF);
    match(TOKEN_LPAREN);
    E();
    match(TOKEN_RPAREN);
    match(TOKEN_LBRACE);
    B();
    match(TOKEN_RBRACE);
    P();
}
void P()
{
    if (current.type == TOKEN_ELSE)
    {
        match(TOKEN_ELSE);
        match(TOKEN_LBRACE);
        B();
        match(TOKEN_RBRACE);
    }
}
void Y()
{
    match(TOKEN_WHILE);
    match(TOKEN_LPAREN);
    E();
    match(TOKEN_RPAREN);
    match(TOKEN_LBRACE);
    B();
    match(TOKEN_RBRACE);
}
void Z()
{
    match(TOKEN_PRINT);
    match(TOKEN_LPAREN);
    if (current.type == TOKEN_STRING)
    {
        match(TOKEN_STRING);
    }
    else
    {
        E();
    }
    match(TOKEN_RPAREN);
    match(TOKEN_SEMICOLON);
}
void E()
{
    T();
    EP();
}
void EP()
{
    if (current.type == TOKEN_PLUS)
    {
        match(TOKEN_PLUS);
        T();
        EP();
    }
    else if (current.type == TOKEN_MINUS)
    {
        match(TOKEN_MINUS);
        T();
        EP();
    }
}
void T()
{
    F();
    TP();
}
void TP()
{
    if (current.type == TOKEN_MULT)
    {
        match(TOKEN_MULT);
        F();
        TP();
    }
    else if (current.type == TOKEN_DIV)
    {
        match(TOKEN_DIV);
        F();
        TP();
    }
}
void F()
{
    L();
    FP();
}
void FP()
{
    if (current.type == TOKEN_LT)
    {
        match(TOKEN_LT);
        L();
        FP();
    }
    else if (current.type == TOKEN_LTE)
    {
        match(TOKEN_LTE);
        L();
        FP();
    }
    else if (current.type == TOKEN_GT)
    {
        match(TOKEN_GT);
        L();
        FP();
    }
    else if (current.type == TOKEN_GTE)
    {
        match(TOKEN_GTE);
        L();
        FP();
    }
    else if (current.type == TOKEN_EQ)
    {
        match(TOKEN_EQ);
        L();
        FP();
    }
    else if (current.type == TOKEN_NEQ)
    {
        match(TOKEN_NEQ);
        L();
        FP();
    }
}
void L()
{
    if (current.type == TOKEN_ID)
    {
        if (!find(&ids, current.name))
        {
            error(TOKEN_INVALID);
        }
        match(TOKEN_ID);
    }
    else if (current.type == TOKEN_NUMBER)
    {
        match(TOKEN_NUMBER);
    }
    else if (current.type == TOKEN_LPAREN)
    {
        match(TOKEN_LPAREN);
        E();
        match(TOKEN_RPAREN);
    }
    else
    {
        error(TOKEN_INVALID);
    }
}

void parse()
{
    current = getNextToken();

    A();

    if (current.type == TOKEN_EOF)
        printf("Cadena valida\n");
    else
        error(TOKEN_INVALID);
}
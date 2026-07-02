#ifndef PARSER_H
#define PARSER_H

/*

A -> begin B end
B -> CB | e
C -> W | X | Y | Z

W -> I=E
X -> if(E){B}P
P -> else{B} | e
Y -> while(B)
Z -> print(B)
Z -> print(S)

E -> TE'
E' -> +TE' | -TE' | e

T  -> FT'
T' -> *FT' | /FT' | e


F -> LF'
F' -> <LF' | >LF' | <=LF' | >=LF' | ==LF' | !=LF' | e

L -> I
L -> N
L -> (E)

I -> [A-Za-z_][A-Za-z0-9_]*
N -> [0-9][0-9]*
S -> "[A-Za-z0-9_]*"

*/

void parse();

#endif
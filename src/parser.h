#ifndef PARSER_H
#define PARSER_H

/*

A -> begin B end
B -> CB | e
C -> W | X | Y | Z

W -> I=E;
X -> if(E){B}P
P -> else{B} | e
Y -> while(E){B}
Z -> print(E);
Z -> print(S);

E -> TE'
E' -> +TE' | -TE' | e

T  -> FT'
T' -> *FT' | /FT' | e


F -> LF'
F' -> <LF' | <=LF' | >LF' | >=LF' | ==LF' | !=LF' | e

L -> I
L -> N
L -> (E)

I -> [A-Za-z_][A-Za-z0-9_]*
N -> [0-9][0-9]*
S -> "[A-Za-z0-9_]*"

*/

void parse();

void A();
void B();
void C();
void W();
void X();
void P();
void Y();
void Z();
void E();
void EP();
void T();
void TP();
void F();
void FP();
void L();

#endif
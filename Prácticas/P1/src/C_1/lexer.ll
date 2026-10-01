%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.hpp"
#include "Lexer.hpp"

using namespace C_1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="C_1::Lexer"
%option case-insensitive


DIG [0-9]
LETRA [a-zA-Z]
ID_ [a-zA-Z_][a-zA-Z0-9_]*
ESPACIO [ \t\n\r]
NUM {DIG}+(\.{DIG}+)?([eE][+-]?{DIG}+)?

%%

{ESPACIO}+  { /* Ignorar espacios en blanco */ }

"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"int" { return INT; }
"float" { return FLOAT; }

{ID_} {return ID; }
{NUM} {return NUMERO; }
"+" {return MAS; }
"-" {return MENOS; }
"*" {return MUL; }
"/" {return DIV; }
"=" {return ASIG; }
"(" {return LPAR; }
")" {return RPAR; }
"," {return COMA; }
";" {return PYC; }

.   { cout << "ERROR LEXICO" << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}


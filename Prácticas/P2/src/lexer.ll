%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"


DIG [0-9]
ID_ [_a-zA-Z][a-zA-Z0-9_]*
NUM {DIG}+(\.{DIG}+)?([eE][+-]?{DIG}+)?

%%
    /*Se definen los tokens que se van a reconocer. Estos se conforman del conjunto de los elementos terminales, como se ve, se remplasa el terminal numero por la expresion regular que lo define ({NUM}) y el terminal identificador por la expresion regular que lo define ({ID})*/
"int" {return t_int; }
"float" {return t_float; }
"=" {return t_equal; }
";" {return t_pyc; }
"," {return t_coma; }
"if" {return t_if; }
"(" {return t_lpar; }
")" {return t_rpar; }
"else" {return t_else; }
"while" {return t_while; }
"+" {return t_mas; }
"-" {return t_menos; }
"*" {return t_mul; }
"/" {return t_div; }
    /*Se ponen hasta el final ya que se elige el token mas largo y si hay algun empate la regla que aparece primero*/
{NUM} { return t_numero; }
{ID_} {return t_id; }

[ \t\r]+ {}
"\n" 	 {line++;}

.    	 { cout << "ERROR LEXICO " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}


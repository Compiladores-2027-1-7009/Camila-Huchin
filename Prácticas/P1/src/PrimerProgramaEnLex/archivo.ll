%{
  #include <iostream>
%}

%option c++
%option noyywrap

digito    [0-9]
hexdigito [0-9a-fA-F]
espacio   [ \t\n]

%%

{espacio}+ { std::cout << "Espacio en blanco" << std::endl; }

0[xX]{hexdigito}+ { std::cout << "Hexadecimal: " << yytext << std::endl; }

int|float|while|return|class {
    std::cout << "Palabra reservada: " << yytext << std::endl;
}

[a-zA-Z_][a-zA-Z0-9_]{0,31} {
    std::cout << "Identificador: " << yytext << std::endl;
}

{digito}+ { std::cout << "Numero: " << yytext << std::endl; }

%%

int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
}
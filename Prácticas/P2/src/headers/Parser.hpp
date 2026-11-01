#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Lexer.hpp"
#include "Symbols.hpp"
using namespace std;

namespace C_1
{
  class Parser
  {

  private:
    Lexer *lexer;
    Token token;
    
  public:
    Parser();
    Parser(Lexer *lexer);
    ~Parser();
    
    void programa(); //función del símbolo incial
    void declaraciones();
    void declaracionesP();
    void declaracion();
    void tipo();
    void lista_var();
    void lista_varP();
    void sentencias();
    void sentenciasP();
    void sentencia();
    void E();
    void EP();
    void T();
    void TP();
    void F();

    void match(Token esperado);
    string nombre(Token t);
    
    Token eat();
    void error(string msg);
    void parse();
  };    
    
}


#endif

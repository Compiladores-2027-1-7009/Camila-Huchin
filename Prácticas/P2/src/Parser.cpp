#include "headers/Parser.hpp"
#include <iostream>

namespace C_1
{
  Parser::Parser(/* args */)
  {
  }

  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }

  void Parser::programa(){
    declaraciones();
    sentencias();
  }

  /************************************************************************/
  /**                                                                    **/
  /**                       Funciones por cada NT                        **/
  /**                                                                    **/
  /************************************************************************/

  /* declaraciones → declaracion declaraciones' */
  void Parser::declaraciones(){
    declaracion();
    declaracionesP();
  }

  /* declaraciones' → declaracion declaraciones' | ε
     Alternativa 1 si token ∈ {int, float}.
     ε si token ∈ FOLLOW = {identificador, if, while}. */
  void Parser::declaracionesP(){
    if(token == t_int || token == t_float){
      declaracion();
      declaracionesP();
    }
  }

  /* declaracion → tipo lista_var ; */
  void Parser::declaracion(){
    tipo();
    lista_var();
    match(t_pyc); 
  }

  /* tipo → int | float */
  void Parser::tipo(){
    if(token == t_int)        match(t_int);
    else if(token == t_float) match(t_float);
    else error("se esperaba un tipo (int o float)");
  }

  /* lista_var → identificador lista_var' */
  void Parser::lista_var(){
    match(t_id);
    lista_varP();
  }

  /* lista_var' → , identificador lista_var' | ε
     ε si token = ';' (FOLLOW). */
  void Parser::lista_varP(){
    if(token == t_coma){
      match(t_coma);
      match(t_id);
      lista_varP();
    }
  }

  /* sentencias → sentencia sentencias' */
  void Parser::sentencias(){
    sentencia();
    sentenciasP();
  }

  /* sentencias' → sentencia sentencias' | ε
     Alternativa 1 si token ∈ {identificador, if, while}.
     ε si token = EOF (FOLLOW). */
  void Parser::sentenciasP(){
    if(token == t_id || token == t_if || token == t_while){
      sentencia();
      sentenciasP();
    }
  }

  /* sentencia → identificador = E ;
               | if ( E ) sentencia else sentencia
               | while ( E ) sentencia */
  void Parser::sentencia(){
    if(token == t_id){
      match(t_id);
      match(t_equal);
      E();
      match(t_pyc);
    }
    else if(token == t_if){
      match(t_if);
      match(t_lpar);
      E();
      match(t_rpar);
      sentencia();
      match(t_else);
      sentencia();
    }
    else if(token == t_while){
      match(t_while);
      match(t_lpar);
      E();
      match(t_rpar);
      sentencia();
    }
    else
      error("se esperaba una sentencia (identificador, if o while)");
  }

  /* E → T E' */
  void Parser::E(){
    T();
    EP();
  }

  /* E' → + T E' | - T E' | ε
     ε si token ∈ {;, )} (FOLLOW). */
  void Parser::EP(){
    if(token == t_mas){
      match(t_mas);
      T();
      EP();
    }
    else if(token == t_menos){
      match(t_menos);
      T();
      EP();
    }
  }

  /* T → F T' */
  void Parser::T(){
    F();
    TP();
  }

  /* T' → * F T' | / F T' | ε
     ε si token ∈ {+, -, ;, )} (FOLLOW). */
  void Parser::TP(){
    if(token == t_mul){
      match(t_mul);
      F();
      TP();
    }
    else if(token == t_div){
      match(t_div);
      F();
      TP();
    }
  }

  /* F → identificador | numero | ( E ) */
  void Parser::F(){
    if(token == t_id)          match(t_id);
    else if(token == t_numero) match(t_numero);
    else if(token == t_lpar){
      match(t_lpar);
      E();
      match(t_rpar);
    }
    else error("se esperaba identificador, numero o '('");
  }

  void Parser::match(Token esperado){
    if(token == esperado)
      eat();
    else
      error("se esperaba '" + nombre(esperado) + "'");
  }

  string Parser::nombre(Token t){
    switch(t){
      case t_int:    return "int";
      case t_float:  return "float";
      case t_id:     return "identificador";
      case t_numero: return "numero";
      case t_equal:  return "=";
      case t_pyc:    return ";";
      case t_coma:   return ",";
      case t_if:     return "if";
      case t_else:   return "else";
      case t_while:  return "while";
      case t_lpar:   return "(";
      case t_rpar:   return ")";
      case t_mas:    return "+";
      case t_menos:  return "-";
      case t_mul:    return "*";
      case t_div:    return "/";
      case t_eof:    return "fin de archivo";
      default:       return "desconocido";
    }
  }


  Token Parser::eat(){
    token = (Token) lexer->yylex(); 
    return token;
  }

  void Parser::error(string msg){
  cout << "ERROR DE SINTAXIS " << msg << " (se encontró '" << nombre(token)
       << "') en la línea " << lexer->getLine() << endl;
  exit(1);
}

  void Parser::parse(){
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

}

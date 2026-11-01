#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G(N, T, P, S)
 *
 * G = (N, T, P, S)
 *
 * N = { programa, declaraciones, declaracionesP, declaracion, tipo,
 *       lista_var, lista_varP, sentencias, sentenciasP, sentencia,
 *       E, EP, T, TP, F }
 *
 * T = { int, float, id, =, ;, ",", if, (, ), else, while,
 *       +, -, *, /, numero }
 *
 * S = programa
 *
 * P = {
 *   programa       ::= declaraciones sentencias
 *
 *   declaraciones  ::= declaracion declaracionesP
 *   declaracionesP ::= declaracion declaracionesP | ε
 *   declaracion    ::= tipo lista_var ;
 *   tipo           ::= int | float
 *   lista_var      ::= id lista_varP
 *   lista_varP     ::= , id lista_varP | ε
 *
 *   sentencias     ::= sentencia sentenciasP
 *   sentenciasP    ::= sentencia sentenciasP | ε
 *   sentencia      ::= id = E ;
 *                    | if ( E ) sentencia else sentencia
 *                    | while ( E ) sentencia
 *
 *   E              ::= T EP
 *   EP             ::= + T EP | - T EP | ε
 *   T              ::= F TP
 *   TP             ::= * F TP | / F TP | ε
 *   F              ::= id | numero | ( E )
 * }
 */


/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { t_eof = 0, t_int, t_float, t_id, t_equal, t_pyc, t_coma, t_if, t_lpar, t_rpar, t_else, t_while, t_mas, t_menos, t_mul, t_div, t_numero };

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { strEmpty, programa, declaraciones, declaracionesP, declaracion, tipo, lista_var, lista_varP, sentencias, sentenciasP, sentencia, E, EP, T, TP, F};

#endif // !__SYMBOLS_HPP__

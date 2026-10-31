#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G(N, T, P, S)
 *
 */

/**
 *programa ::= declaraciones sentencias
 */


/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { primero, t_eof, t_int , t_float, t_id, t_equal, t_pyc, t_coma, t_if, t_lpar, t_rpar, t_else, t_while, t_mas, t_menos, t_mul, t_div, t_numero};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { strEmpty, programa, declaraciones, sentencias};

#endif // !__SYMBOLS_HPP__

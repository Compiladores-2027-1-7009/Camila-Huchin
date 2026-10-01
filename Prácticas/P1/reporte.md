# Práctica 1: Primer programa en Lex/Flex

**Nombre:** [Camila Hernandez Huchin]
**Materia:** [Compiladores]

## 1. Introducción

En esta práctica se usó Flex para construir analizadores léxicos en C++. Un archivo `.ll` describe con expresiones regulares y acciones cómo reconocer los lexemas de una entrada. Flex lo traduce a código C++ que se compila con `g++`.

La práctica tiene dos partes:

1. Un primer programa que reconoce números y palabras.
2. Un analizador léxico para un lenguaje pequeño (`C_1`) que se prueba con un archivo de entrada.

## 2. De `.ll` a ejecutable

1. `flex++ archivo.ll` genera el código C++ del escáner (`lex.yy.cc` o `Lexer.cpp`).
2. `g++` realiza el preprocesamiento (se insertan los `#include`), la compilación (C++ a ensamblador), el ensamblado (ensamblador a código objeto `.o`) y el enlazado (se unen los objetos y las bibliotecas para formar el ejecutable).

## 3. Parte 1: Primer programa en Lex

### Procedimiento

```
flex++ archivo.ll
ls                              # se comprueba que existe lex.yy.cc
g++ lex.yy.cc -o ejecutable
./ejecutable
```
El programa espera una entrada que realizara el analisis de tockens

### Ejercicios

**1. ¿Qué ocurre si se quitan las llaves a la macro `letra`?**
Flex ya no sustituye la macro y toma `letra+` como texto literal. Solo se reconoce la cadena `letra` (por ejemplo `letraa`), y cualquier otra palabra ya no se detecta.

```
letraletraletraletra
Encontré una palabra: letra
Encontré una palabra: letra
Encontré una palabra: letra
Encontré una palabra: letra

a
a
ho
ho
```

**2. ¿Qué ocurre si se quitan las llaves a las macros en la segunda sección?**
Pasa lo mismo: los nombres se toman como texto literal. `digito` y `palabra` solo reconocen esas cadenas exactas. Además, `espacio` deja de ignorar los espacios y saltos de línea, que ahora se copian a la salida.

```
digito
Encontré un número: digito
palabra
Encontré una palabra: palabra
letra
letra
```

**3. ¿Cómo se escribe un comentario en flex?**
Con la sintaxis de C: `/* comentario */`. En la sección de reglas deben ir indentados o dentro de las llaves de una acción. En el código C++ también se puede usar `//`.

**4. ¿Qué se guarda en `yytext`?**
El lexema: la cadena de entrada que coincidió con el patrón de la regla activa. Su longitud está en `yyleng`.

**5. ¿Qué pasa al introducir cadenas de caracteres y dígitos?**
El programa reconoce palabras y números e imprime un mensaje por cada uno. Los espacios y saltos de línea se ignoran porque su regla tiene una acción vacía. Los demás caracteres (paréntesis, llaves, `=`, `;`) no coinciden con ninguna regla y se copian tal cual a la salida.

```
public static void main (args) {int num = 9;}
Encontré una palabra: public
Encontré una palabra: static
Encontré una palabra: void
Encontré una palabra: main
(Encontré una palabra: args
){Encontré una palabra: int
Encontré una palabra: num
=Encontré un número: 9
```

**6. ¿Qué ocurre con caracteres como `*`?**
No coinciden con ninguna regla, así que flex aplica su regla por defecto, que copia el carácter a la salida sin ejecutar ninguna acción. Se ve el `*` impreso, pero sin mensaje.

**7. Programa con hexadecimales, palabras reservadas, identificadores y espacios**

Expresiones usadas:

- Hexadecimales: `0[xX][0-9a-fA-F]+`
- Identificadores de máximo 32 caracteres: `[a-zA-Z_][a-zA-Z0-9_]{0,31}`
- Las palabras reservadas van antes que los identificadores, porque en un empate de longitud flex elige la primera regla.
- Gana siempre el lexema más largo, por eso `whilex` es un identificador.

```
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
```

## 4. Parte 2: Analizador léxico de C_1

### Ejercicio 8: terminales y expresiones regulares

| Código | Terminal | Expresión regular |
|---|---|---|
| 1 | MAS | `"+"` |
| 2 | MENOS | `"-"` |
| 3 | MUL | `"*"` |
| 4 | DIV | `"/"` |
| 5 | ASIG | `"="` |
| 6 | LPAR | `"("` |
| 7 | RPAR | `")"` |
| 8 | COMA | `","` |
| 9 | PYC | `";"` |
| 10 | ID | `[a-zA-Z_][a-zA-Z0-9_]*` |
| 11 | IF | `"if"` |
| 12 | INT | `"int"` |
| 13 | WHILE | `"while"` |
| 14 | ELSE | `"else"` |
| 15 | FLOAT | `"float"` |
| 16 | NUMERO | `[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?` |
| 17 | ESP | `[ \t\n\r]+` (se ignora) |

Notas:

- `if3` y `while4` salen como ID porque gana el lexema más largo.
- `12345` y `1.2e6` son el mismo terminal (NUMERO).
- Con `case-insensitive`, `IF` y `If` también son palabras reservadas.

### Ejercicio 9: acciones léxicas

`main.cpp` llama a `yylex()` en un ciclo e imprime `código, lexema`. Por eso las acciones solo devuelven el código del token (`return IF;`, etc.) y no imprimen nada. Los espacios tienen una acción vacía para ser ignorados.

```
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
```

Ejecución:

```
flex++ lexer.ll
g++ Lexer.cpp main.cpp -o compiler
./compiler prueba
```

Salida:

```
12, int
15, float
11, if
14, else
13, while
12, int
16, 12345
16, 1.2e6
10, a1
10, a_23
10, ___
10, id2
10, if3
10, while4
10, _b
9, ;
8, ,
6, (
7, )
12, int
7, )
10, a
10, _qbc
```


La salida coincide con la esperada.

### Ejercicio 10: Makefile

```make
CXX  = g++
FLEX = flex++

all: compiler

Lexer.cpp: lexer.ll
	$(FLEX) lexer.ll

compiler: Lexer.cpp main.cpp Lexer.hpp tokens.hpp
	$(CXX) Lexer.cpp main.cpp -o compiler

run: compiler
	./compiler prueba

clean:
	rm -f compiler Lexer.cpp

.PHONY: all run clean
```

Uso: `make`, `make run`, `make clean`.

```
 make clean
rm -f compiler Lexer.cpp
```

```
make
flex++ lexer.ll
g++ Lexer.cpp main.cpp -o compiler
```
```
make run
./compiler prueba
```

## 5. Problemas encontrados y soluciones

| Problema | Causa | Solución |
|---|---|---|
| `flex: can't open −−version` | Los guiones eran el carácter Unicode "−", no `-`. | Escribir el comando a mano: `flex --version`. |
| `xxd: command not found` | El contenedor no lo tiene instalado. | Usar `od -c`. |
| `'THEN'`, `'FOR'`, `'CHAR'`, `'VOID'`, `'NUM' was not declared` | El `.ll` devolvía constantes que no existen en `tokens.hpp`; además `NUM` es la macro y la constante es `NUMERO`. | Quitar esas reglas y usar `return NUMERO;`. |
| Los cambios en el `.ll` no se reflejaban | `g++` compilaba el `Lexer.cpp` viejo. | Ejecutar `flex++` antes de compilar (el Makefile lo hace solo). |

## 6. Conclusiones

- Las llaves `{}` indican a flex que expanda una macro; sin ellas el nombre se toma como texto literal.
- Lo que no coincide con ninguna regla se copia a la salida, por eso conviene una regla final `.` para reportar errores léxicos.
- Flex decide por el lexema más largo y, en empate, por la regla que aparece primero.
- `Lexer.cpp` es un archivo generado: hay que regenerarlo con `flex++` tras cada cambio, y el Makefile automatiza esto.
- Posibles mejoras: soportar comentarios, contar líneas para ubicar errores y devolver un token de error en lugar de imprimir.

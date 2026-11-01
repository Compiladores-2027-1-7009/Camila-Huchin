<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2027-1 <br>
  Práctica 1: Analizadores léxicos con Lex (Flex) <br> Profesora: Ariel Adara Mercado Martínez
</p>


# Análisis sintáctico descendente

## Objetivo:
Que el alumno conozca e implemente los principios del análisis sintáctico descendente recursivo, aplicando técnicas de transformación de gramáticas —eliminación de ambigüedad, eliminación de recursividad izquierda y 
factorización izquierda— para construir un analizador sintáctico predictivo que, junto con el analizador léxico desarrollado con Flex, permita reconocer programas válidos del lenguaje C_1.


### Estructura del directorio
```c++
p3
├── README.md
└── src //carpeta de código
    ├── headers
    │   ├── Lexer.hpp   //header de la clase Lexer
    │   ├── Parser.hpp  //header de la clase Parser
    │   └── Symbols.hpp //definición de símbolos
    ├── lexer.ll        //definición del an. léxico
    ├── main.cpp        //contiene la función principal del programa
    ├── Makefile        //boceto de Makefile (no funciona aún)
    ├── Parser.cpp      //código fuente de la clase Parser
    └── prueba          ////archivo de entrada para el analizador (léxico y sintáctico)
```

### Uso

#### Compilación

```bash
$ cd src/
$ flex++ lexer.ll
$ g++ Lexer.cpp Parser.cpp main.cpp -o analyzer
```

#### Ejecución

```bash
$ ./analyzer prueba
```

#### Ejercicios
Para la gramática G = ( N, Σ, P, S), descrita por las siguientes producciones: 
> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaracion | declaracion <br>
>> declaracion → tipo lista_var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresion **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → expresion **+** expresion | expresion **-** expresion | expresion __\*__ expresion | expresion **\/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}


1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) -- con su respectivo PDF, para este último -- , los conjuntos _N_, _Σ_ y el símbolo inicial _S_.  (0.5 pts.)

>_N_ = {programa, declaraciones, declaracion, tipo, lista_var, sentencias, sentencia, expresion}
>_Σ_ = {**;**, **int**, **float**, **,**, _**identificador**_, **=**, **if**, **(**, **)**, **else**, **while**, **+**, **-**, __\*__, **\/**, **_numero_** }
>_S_ = programa

2. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (1 pts.).

Existe ambiguedad en la regla de producción _expresion_ ya que se puede producir la misma cadena de dos árboles de derivación distintos

Ejemplo:
**Cadena:** id + id * id

Derivacion 1 (partiendo de _expresion **+** expresion_)
expresion 
=> expresion **+** expresion 
=> _**identificador**_ **+** expresion 
=> _**identificador**_ **+** expresion __\*__ expresion 
=> _**identificador**_ **+** _**identificador**_ __\*__ expresion 
=> _**identificador**_ **+** _**identificador**_ __\*__ _**identificador**_

Derivacion 2 (partiendo de _expresion __\*__ expresion_)
expresion 
=> expresion __\*__ expresion 
=> expresion **+** expresion __\*__ expresion 
=> _**identificador**_ **+** expresion __\*__ expresion 
=> _**identificador**_ **+** _**identificador**_ __\*__ expresion 
=> _**identificador**_ **+** _**identificador**_ __\*__ _**identificador**_

Eliminamos la ambiguedad en la regla de producción _expresion_:

precedencia de operadores:
*/
+-
id num ()

nuevas producciones:
>E → E **+** T | E **-** T | T 
>T → T __\*__ F | T **\/** F | F
>F → _**identificador**_ | **_numero_** | **(** E **)**

De esta forma, la cadena id + id * id solo puede derivarse de una manera, eliminando la ambiguedad.

Por otro lado, la regla de producción _sentencia_ también es ambigua, ya que se puede producir la misma cadena de dos árboles de derivación distintos.

Ejemplo:
**Cadena:** while ( id ) id = num ; id = num ;

Derivación 1 (el cuerpo del while es solo _id = num;_  la segunda sentencia va después)

sentencias
=> sentencias sentencia
=> sentencia sentencia
=> **while** **(** expresion **)** sentencias sentencia
=> **while** **(** expresion **)** sentencia sentencia
=> **while** **(** expresion **)** _**identificador**_ **=** expresion **;** sentencia
=> **while** **(** expresion **)** _**identificador**_ **=** expresion **;** _**identificador**_ **=** expresion **;**
=> **while** **(** _**identificador**_ **)** _**identificador**_ **=** **_numero_** **;** _**identificador**_ **=** **_numero_** **;**

Derivación 2 (el cuerpo del _while_ es _id = num ; id = num;_ )
sentencias

=> sentencia
=> **while** **(** expresion **)** sentencias
=> **while** **(** expresion **)** sentencias sentencia
=> **while** **(** expresion **)** sentencia sentencia
=> **while** **(** expresion **)** _**identificador**_ **=** expresion **;** sentencia
=> **while** **(** expresion **)** _**identificador**_ **=** expresion **;** _**identificador**_ **=** expresion **;**
=> **while** **(** _**identificador**_ **)** _**identificador**_ **=** **_numero_** **;** _**identificador**_ **=** **_numero_** **;**

La cadena tiene dos árboles de derivación distintos, por lo tanto la gramática es ambigua.

Podemos eliminar esta ambiguedad usando _sentencia_ en el cuerpo en lugar de _sentencias_, de esta forma la producción _sentencia_ queda de la siguiente manera:

>sentencia → _**identificador**_ **=** E **;** | **if** **(** E **)** sentencia **else** sentencia | **while** **(** E **)** sentencia

De esta forma las reglas de producción _P_ queda de la siguiente manera:

> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaracion | declaracion <br>
>> declaracion → tipo lista_var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** E **;** | **if** **(** E **)** sentencia **else** sentencia | **while** **(** E **)** sentencia <br>
>> E → E **+** T | E **-** T | T <br>
>> T → T __\*__ F | T **\/** F | F <br>
>> F → _**identificador**_ | **_numero_** | **(** E **)**
}

_Σ_ y _S_ se mantienen pero el conjunto _N_ queda de la siguiente manera:

>_N_ = {programa, declaraciones, declaracion, tipo, lista_var, sentencias, sentencia, E, T, F}

3. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (1 pts.)

Obsevamos que varias reglas de producción precentan recursividad izquierda, estas son:
> declaraciones → declaraciones declaracion | declaracion 
> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ 
> sentencias → sentencias sentencia | sentencia 
>E → E **+** T | E **-** T | T 
>T → T __\*__ F | T **\/** F | F 

Aplicamos la regla para eliminar la recursividad izquierda:

Si A → Aα| β, entonces A → βA' y A' → αA' | ε

De esta forma, las reglas de producción quedan de la siguiente manera:

> declaraciones → declaracion declaraciones'
> declaraciones' → declaracion declaraciones' | ε <br>
> lista_var → _**identificador**_ lista_var' 
> lista_var' → **,** _**identificador**_ | ε <br>
> sentencias → sentencia sentencias'
> sentencias' → sentencia sentencias'| ε <br>
>E → T E'
>E' → **+** T E'| **-** T E'| ε <br>
>T → F T'
>T' → __\*__ F T'| **\/** F T'| ε <br>

Asi se añaden a los No-Terminales _N_ y al conjunto _P_las siguientes reglas de producción: 

> _N_ = _N_ ∪ {declaraciones', lista_var', sentencias', E', T'}

> _P_ = {
>> programa → declaraciones sentencias
> declaraciones → declaracion declaraciones'
> declaraciones' → declaracion declaraciones' | ε 
> declaracion → tipo lista_var **;** 
> tipo → **int** | **float** 
> lista_var → _**identificador**_ lista_var' 
> lista_var' → **,** _**identificador**_ | ε 
> sentencias → sentencia sentencias'
> sentencias' → sentencia sentencias'| ε 
> sentencia → _**identificador**_ **=** E **;** | **if** **(** E **)** sentencia **else** sentencia | **while** **(** E **)** sentencia 
> E → T E'
> E' → **+** T E'| **-** T E'| ε 
> T → F T'
> T' → __\*__ F T'| **\/** F T'| ε 
>F → _**identificador**_ | **_numero_** | **(** E **)** 
}
 
4. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (1 pts.)

No es necesario realizar factorización izquierda ya que no existen reglas de producción que compartan un prefijo común

5. Mostrar en el archivo los nuevos conjuntos _N_ y _P_. (0.5 pts.)

Como no se realizo factorización izquierda, los conjuntos _N_ y _P_ se mantienen igual que en el punto 3

>N = {programa, declaraciones, declaracion, tipo, lista_var, sentencias, sentencia, E, T, F, declaraciones', lista_var', sentencias', E', T'}

> _P_ = {
>> programa → declaraciones sentencias
> declaraciones → declaracion declaraciones'
> declaraciones' → declaracion declaraciones' | ε 
> declaracion → tipo lista_var **;** 
> tipo → **int** | **float** 
> lista_var → _**identificador**_ lista_var' 
> lista_var' → **,** _**identificador**_ | ε 
> sentencias → sentencia sentencias'
> sentencias' → sentencia sentencias'| ε 
> sentencia → _**identificador**_ **=** E **;** | **if** **(** E **)** sentencia **else** sentencia | **while** **(** E **)** sentencia 
> E → T E'
> E' → **+** T E'| **-** T E'| ε 
> T → F T'
> T' → __\*__ F T'| **\/** F T'| ε 
>F → _**identificador**_ | **_numero_** | **(** E **)** 
}
 

6. Definir el Analizador Léxico (lexer.ll) con las acciones léxicas correspondientes. (2 pts.)
7. Implementar el Analizador Sintáctico (Parser.cpp) de descenso recursivo, documentando las funciones de cada No-Terminal, de forma que el programa descrito en el archivo _prueba_ sea reconocido y aceptado por el analizador resultante. (4 pts.)

---
#### Extras

8. Documentar el código. (0.25pts)
9. Proponer 4 archivos de prueba nuevos, 2 válidos y 2 inválidos. (0.25pts)
10. Modificar el Makefile para poder simplificar el proceso de compilación de la práctica. (1pt)

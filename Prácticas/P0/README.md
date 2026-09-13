<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2027-1 <br>
  Práctica 0: Sistema de procesamiento de Lenguaje <br> Profesora: Ariel Adara Mercado Martínez
</p>

### Sistema de procesamiento de Lenguaje
### Objetivo:
Comprender y analizar el funcionamiento de los diferentes programas que intervienen en el proceso de traducción de un programa fuente a un programa ejecutable.

### Introducción
Un compilador es un programa que traduce un programa fuente escrito en un lenguaje de alto nivel a un
programa en lenguaje objeto, usualmente de bajo nivel. Este proceso no se realiza de manera aislada; el
compilador colabora con otros programas como el preprocesador, ensamblador y enlazador.
El preprocesador recopila y expande macros y otros fragmentos de código abreviado en el programa
fuente. Luego, el compilador transforma el código preprocesado en un programa objeto en lenguaje ensamblador, que es posteriormente convertido en código máquina por el ensamblador. Finalmente, el enlazador combina los archivos de código máquina y bibliotecas necesarias para producir un programa ejecutable. El cargador lleva este programa ejecutable a la memoria para su ejecución.

```mermaid
flowchart TD
subgraph 1
id1([Programa fuente]) --> Preprocesador  -- Programa Fuente modificado -->  Compilador  -- Programa objeto en lenguaje ensamblador -->  Ensamblador  -- Código máquina relocalizable --> Enlazador/Cargador --> id2([Código máquina destino])
end
subgraph  2  
id3[/Archivos de biblioteca y archivos objeto/] --> Enlazador/Cargador  
end  
 ```

### Desarrollo:

1. Deberá tener instalado el compilador _gcc_ y trabajar en un ámbiente _Linux_.
2. Escriba el siguiente programa en lenguaje **_C_** (sin copiar y pegar) y nómbrelo *programa.c*
```c
#include <stdio .h>
#include <stdlib.h>
//# define PI 3.1415926535897

# ifdef PI
# define area (r) (PI * r * r)
# else
# define area (r) (3.1416 * r * r)
# endif


/**
* Compiladores 2025-2
*
*/
int main ( void ) {
printf ("Hola Mundo !\n"); //Función para imprimir hola mundo
float mi_area = area (3) ; //soy un comentario... hasta donde llegaré ?
printf ("Resultado : %f\n", mi_area);
return 0;
}
```

3. Use el siguiente comando: `cpp programa.c programa.i`
Revise el contenido de _programa.i_ y conteste lo siguiente:
<ol type="a">
  <li>¿Qué ocurre cuando se invoca el comando <i>cpp</i> con esos argumentos?</li>

  <p><strong>Respuesta:</strong>Se crea el archivo programa.i</p>

  <li>¿Qué similitudes encuentra entre los archivos <i>programa.c</i> y <i>programa.i</i>?</li>

  <p><strong>Respuesta:</strong>La estructura principal del programa se conserva, incluyendo la funcion main y las instrucciones del programa. Sin embargo, las macros son sustituidas por su contenido, por ejemplo, float mi_area = area(3); se convierte en float mi_area = (3.1416 * 3 * 3);.</p>

  <li>¿Qué pasa con las macros y los comentarios del código fuente original en <i>programa.i</i>?</li>

  <p><strong>Respuesta:</strong> Los comentarios se eliminan y las macros son procesadas y sustituidas por su contenido., por eso es el cambio de area(3) ->(3.1416 * 3 * 3)</p>

  <li>Compare el contenido de <i>programa.i</i> con el de <i>stdio.h</i> e indique de forma general las similitudes entre ambos
  archivos.</li>

  <p><strong>Respuesta:</strong> ambos tienen declaraciones similares en C, de hecho, parece que .i contiene ciertas partes de stdio.h, como las declaraciones de tipos</p>

  <li>¿A qué etapa corresponde este proceso?</li>

  <p> <strong>Respuesta:</strong> Al ejecutar cpp se crea el archivo con la extención .i , este, al no tener comentarios ni tener macros, pero al no estar aun en lenguaje ensamblador, supondria que se trata del <strong>preprocesador</strong>, el cual el .i seria el programa fuente modificado </p>

</ol>

---

4. Ejecute la siguiente instrucción: ``gcc -Wall -S programa.i``
<ol type="a">
  <li>¿Para qué sirve la opción <i>-Wall</i>?</li>

  <p><strong>Respuesta:</strong> warning all: activa la mayoría de las advertencias importantes del compilador: variables sin inicializar, conversiones sospechosas, funciones sin prototipo, etc.</p>
  <!--(https://mundobytes.com/tutorial-completo-del-comando-gcc-y-sus-opciones-clave/) -->

  <li>¿Qué le indica a gcc la opción <i>-S</i>?</li>

  <p><strong>Respuesta:</strong>  Que tiene que compilar, sin ensamblar. </p>

  <!--(https://mundobytes.com/tutorial-completo-del-comando-gcc-y-sus-opciones-clave/) -->

  <li>¿Qué contiene el archivo de salida y cuál es su extensión?</li>

  <p><strong>Respuesta:</strong> Genera código ensamblador en un archivo con extensión .s.</p>

  <!--(https://mundobytes.com/tutorial-completo-del-comando-gcc-y-sus-opciones-clave/) -->

  <li>¿A qué etapa corresponde este comando?</li>

  <p><strong>Respuesta:</strong> Al <strong>Compilador</strong>, ya que desde un programa fuente modificado (programa.i), el compilador genera un programa objeto en lenguaje ensamblador (programa.s) </p>

</ol>

---

1. Ejecute la siguiente instrucción: `as programa.s -o programa.o`
<ol type="a">
  <li> Antes de revisarlo, indique cuál es su hipótesis sobre lo que debe contener el archivo con extensión  <i>.o</i>. </li>

 <p><strong>Respuesta:</strong>Seria el programa objeto </p>

  <li> Diga de forma general qué contiene el archivo <i>programa.o</i> y por qué se visualiza de esa manera. </li>

  <p><strong>Respuesta:</strong> Simbolos que la computadora no reconoce y unas cuantas cadenas que se habian declarado en el .c</p>

  <li> ¿Qué programa se invoca con  <i>as</i>? </li>

  <p><strong>Respuesta:</strong> Assembler</p>

  <li> ¿A qué etapa corresponde la llamada a este programa? </li>

  <p><strong>Respuesta:</strong><strong>Enlazador/Cargador</strong> y el archivo .o es el codigo de maquina destino, en este caso a lenguaje ensamblador </p>

</ol>

---

1. Encuentre la ruta de los siguientes archivos en el equipo de trabajo:
* ld-linux-x86-64.so.2
* Scrt1.o (o bien, crt1.o)
* crti.o
* crtbeginS.o
* crtendS.o
* crtn.o

---

7. Ejecute el siguiente comando, sustituyendo las rutas que encontró en el paso anterior:
```bash
ld -o ejecutable -dynamic-linker /lib/ld-linux-x86-64.so.2 /usr/lib/Scrt1.o /usr/lib/crti.o programa.o -lc /usr/lib/crtn.o
```

<ol type="a">
  <li> En caso de que el comando ld mande errores, investigue como enlazar un programa utilizando el comando <i>ld</i>. Y proponga una posible solución para llevar a cabo este proceso con éxito. </li>
  <li> Describa el resultado obtenido al ejecutar el comando anterior. </li>

  <p><strong>Respuesta:</strong> Se creo el archivo ejecutable con un monton de simbolo que el editor de texto no reconoce</p>

</ol>

---
8. Una vez que se enlazó el código máquina relocalizable, podemos ejecutar el programa con la siguiente
instrucción en la terminal: ```./ejecutable```
<p><strong>Resultado:</strong> </p>
<p>Hola Mundo</p>
<p>Resultado: 28.274401</p>

---

9. Quite el comentario de la macro _#define PI_ en el código fuente original y conteste lo siguiente:
<ol type="a">
  <li> Genere nuevamente el archivo.i. De preferencia asigne un nuevo nombre.</li>
  <li> ¿Cambia en algo la ejecución final? </li>

  <p><strong>Resultado:</strong>Si, los ultimos digitos, por la precisión de PI </p>
<p>Hola Mundo</p>
<p>Resultado: 28.274334</p>

</ol>

---

1.  Escribe un segundo programa en lenguaje **_C_** en el que agregue 4 directivas del preprocesador
de _**C**_ (_cpp_)[^1]. Las directivas elegidas deben jugar algún papel en el significado del programa, ser distintas entre sí y
diferentes de las utilizadas en el primer programa (aunque no están prohibidas si las requieren). 
<ol type="a">
    <li>Explique su utilidad
general y su función en particular para su programa.</li>

<p><strong>Respuesta:</strong> </p>

<p>Programa realizado: programa2.c </p>

<p>El programa programa2.c permite ingresar hasta diez calificaciones de un alumno. Después de cada calificación, pregunta si se desea ingresar otra y verifica que el valor se encuentre dentro de la escala seleccionada. Al finalizar, calcula y muestra el promedio e indica si el alumno está aprobado o reprobado según la calificación mínima correspondiente a la escala utilizada.</p>

<p><strong>Utilidad y funcion de las directivas</strong> </p>

<p><strong>#ifndef:</strong> Comprobar si la macro (en este caso ESCALA) no ha sido definida, en ese caso, definir su valor predeterminado como 10</p>
<p><strong>#if:</strong> Evaluar una condicion de una macro (escala), si esta se cumple se realizara cierta accion o modificación  en ese caso, ver su ESCALA esta definida como 10, si sí, entondes establecer un minimo aprobado 6</p>
<p><strong>#elif: </strong> En caso que la macro (escala) no haya cumplido la condicion de #if, se puede evaluar otra condicion,  en ese caso, si escala esta definida como 100, de ser asi, define la calificacion minima aprobatoria como 60 </p>
<p><strong>#error:</strong> Comunicar un error durante el preprocesamiento, aqui se usa para impedir la compilacion si la escala es diferente de 10 o 100</p>

</ol>

---

11. Redacte un informe detallado con sus resultados y conclusiones.

<p>Existen diferentes programas que permiten observar las distintas etapas del proceso de compilación de programas escritos en <strong>C</strong>. Estos programas generan archivos intermedios que permiten analizar cómo se transforma el código fuente hasta obtener un programa ejecutable. Durante la práctica se utilizaron los siguientes:</p>

*<strong>cpp</strong>: Se encarga del <strong>preprocesamiento</strong> del código fuente. Genera un archivo <strong>.i</strong>, en el cual se procesan las directivas del preprocesador, se eliminan los comentarios y se sustituyen las macros. Además, se incorporan los contenidos de los archivos incluidos mediante <strong> # include </strong>.

*<strong>gcc</strong>: Se encarga de realizar la <strong>compilación</strong> del código preprocesado y puede generar un archivo <strong>.s</strong>, que contiene el programa traducido a <strong>lenguaje ensamblador</strong>, pero que todavía no ha sido ensamblado.

*<strong>as</strong>: Se encarga de <strong>ensamblar</strong> el archivo <strong>.s</strong> y convertirlo en un archivo objeto <strong>.o</strong>. El archivo objeto contiene código máquina, pero todavía no constituye un programa ejecutable completo.

*<strong>ld</strong>: Se encarga del <strong>enlazado</strong>. Toma el archivo objeto y los archivos necesarios para el inicio y funcionamiento del programa, además de las bibliotecas requeridas, y los combina para generar el archivo ejecutable final.

<p>Durante la práctica se observo que el proceso de compilación no ocurre en un solo paso, sino que se forma por varias etapas. A partir de un archivo fuente <strong>.c</strong>, el código pasa por el preprocesamiento, la compilación, el ensamblado y finalmente el enlazado.</p>

<p>El análisis de los archivos intermedios permite observar los cambios que sufre el programa en cada etapa. Por ejemplo, en el archivo <strong>.i</strong> se puede observar el efecto de las directivas del preprocesador y el contenido incorporado mediante <strong>#include</strong>. El archivo <strong>.s</strong> muestra la transformación del programa a lenguaje ensamblador, mientras que el archivo <strong>.o</strong> contiene el código objeto que posteriormente será utilizado por el enlazador.</p>

<p>También se comprobó que es posible realizar estas etapas de manera independiente utilizando las herramientas correspondientes. Esto permite comprender con mayor claridad qué sucede internamente durante la compilación de un programa en C y facilita la identificación de errores en las diferentes etapas.</p>

<h6>Conclusión</h6>

<p>La práctica permitió comprender que la generación de un programa ejecutable en C es un proceso compuesto por diferentes etapas. El uso de <strong>cpp</strong>, <strong>gcc</strong>, <strong>as</strong> y <strong>ld</strong> permite observar y analizar los archivos intermedios generados durante dicho proceso. Esto ayudó a comprender la función que cumple cada herramienta y la transformación que experimenta el código fuente hasta convertirse en un programa ejecutable.</p>


[^1]: Pueden consultar la lista de directivas en su documentación en línea: [CPP - Index of directives](https://gcc.gnu.org/onlinedocs/cpp/Index-of-Directives.html##Index-of-Directives). O bien, revisar la entrada para este preprocesador en la herramienta man en Linux: `$ man cpp`


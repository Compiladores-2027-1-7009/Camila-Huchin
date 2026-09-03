#include <stdio.h>
#include <stdlib.h>

//#define PI 3.14159265358979323846

#ifdef PI

#define area(r) (PI * r * r)

#else

#define area(r) (3.1416 * r * r)

#endif


/**
* Compiladores 2027-1
*
*/
int main(void){
    printf("Hola Mundo\n");//Función para imprimir hola mundo
    float mi_area = area(3);//soy un comentario... hasta donde llegaré ?
    printf("Resultado: %f\n", mi_area);
    return 0;
}
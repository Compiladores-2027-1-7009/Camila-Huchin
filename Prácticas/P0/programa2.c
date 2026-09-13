#include <stdio.h>

//#define ESCALA 100

#ifndef ESCALA
#define ESCALA 10
#endif

#if ESCALA == 10
    #define MIN_APROBADO 6
#elif ESCALA == 100
    #define MIN_APROBADO 60
#else
    #error "ESCALA no válida. Debe ser 10 o 100."
#endif

int main(void) {
    
    float calificaciones[10]; 
    int cantidad = 0; 
    char respuesta; 
    float suma = 0; 
    float promedio; 
    float calificacion;

    do{
        do{
            printf("Ingresa una calificacion: "); 
            scanf("%f", &calificacion); 
            if (calificacion < 0 || calificacion > ESCALA) { 
                printf("Calificacion invalida. Debe estar entre 0 y %.0f.\n", (float)ESCALA); 
            } 
        } while (calificacion < 0 || calificacion > ESCALA);
        
        calificaciones[cantidad] = calificacion; 
        
        cantidad++; 

        if (cantidad < 10) { 
            printf("Hay mas calificaciones? (s/n): "); 
            scanf(" %c", &respuesta); 
        } else { 
            respuesta = 'n'; 
        } 
    }while (respuesta == 's' || respuesta == 'S');

    for(int i = 0; i < cantidad; i++){
        suma += calificaciones[i];
    }

    promedio = suma / cantidad;

    printf("Promedio: %.2f\n", promedio);

    if(promedio >= MIN_APROBADO){
        printf("El estudiante aprobó.\n");
    } else {
        printf("El estudiante reprobó.\n");
    }

    return 0;
}
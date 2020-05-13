
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "Simulacion.h"
#include "tools.h"
int main(int argc, char** argv) {
    
    
    
    FILE* fichero;
    fichero = fopen("fichero", "r");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    }
    int f,c;
    fscanf(fichero, "%d %d" , &f, &c);
    int opcion;
    scanf("%d",&opcion);
    dibujarCuadro(f,c);
    crearSimulacion(f, c);
    run(argv[0]);
    
    return (EXIT_SUCCESS);
}


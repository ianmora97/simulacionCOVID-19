
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <ncurses.h>
#include <time.h>
#include "Simulacion.h"
#include "tools.h"



int main(int argc, char** argv) {
    srand(time(0));

   
    FILE* fichero;
    fichero = fopen("fichero", "r");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    }
    int f, c;
    fscanf(fichero, "%d %d", &f, &c);
    int op;
    scanf("%d",&op);
    initscr();
    cbreak();
    curs_set(0);
    system("clear");
    dibujarCuadro(f, c);
    crearSimulacion(f, c);
    run(0);
    refresh();
    getch();
    endwin();
    return (EXIT_SUCCESS);
}

